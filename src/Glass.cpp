#include "..\includes\Common.h"
using namespace std;

string Lexer::TrimmedLine;
vector<string> Lexer::Tokens;

bool Lexer::BracketsNQuotes()
{
    string NonStringData = InString::ExcludeDataInString(TrimmedLine);

    // Double and Single quotes
    int SQUOTE = Collections::String::Count(NonStringData, "'");
    int DQUOTE = Collections::String::Count(NonStringData, "\"");

    // Parenthesis
    int LPAREN = Collections::String::Count(NonStringData, "(");
    int RPAREN = Collections::String::Count(NonStringData, ")");

    // Square brackets
    int LSQUARE = Collections::String::Count(NonStringData, "[");
    int RSQUARE = Collections::String::Count(NonStringData, "]");
    
    if ((SQUOTE != 0 && !Strings::IsEven(SQUOTE)) || (DQUOTE != 0 && !Strings::IsEven(DQUOTE)))
    {
        Error::Syntax("Unterminated string literal");
        return true;
    }

    else if (LPAREN != 0 || RPAREN != 0)
    {
        if (LPAREN > RPAREN)
        {
            Error::Syntax("'(' was never closed");
            return true;
        }

        else if (LPAREN < RPAREN)
        {
            Error::Syntax("Unmatched ')'");
            return true;
        }
    }

    else if (LSQUARE != 0 || RSQUARE != 0)
    {
        if (LSQUARE > RSQUARE)
        {
            Error::Syntax("'[' was never closed");
            return true;
        }

        else if (LSQUARE < RSQUARE)
        {
            Error::Syntax("Unmatched ']'");
            return true;
        }
    }

    return false;
}

Lexer::Lexer()
{
    TrimmedLine = Strings::Trim(CurrentLine);
    if (!BracketsNQuotes()) Tokenizer();
}

void Lexer::Tokenizer()
{
    string Lexemes = "";
    string NonStringStr = InString::ExcludeDataInString(TrimmedLine);
    string NoSpaceLexeme = "";

    int StrIdx = 0;
    bool IsString = false;

    vector<string> Toks;    
    vector<string> String = InString::DataInString(TrimmedLine);
    for (int i = 0; i < NonStringStr.size(); i++)
    {
        Lexemes += Strings::ToString(NonStringStr[i]);
        if (Strings::Endswith(Lexemes, "//")) break;
        else if (Strings::Endswith(Lexemes, " "))
        {
            NoSpaceLexeme = Lexemes.substr(0, Lexemes.size() - 1);
            if (!Collections::String::IsEmpty(NoSpaceLexeme)) Toks.push_back(NoSpaceLexeme);
            Toks.push_back(Strings::ToString(NonStringStr[i]));
            Lexemes = "";
        }

        else if (Strings::Endswith(Lexemes, "\"") || Strings::Endswith(Lexemes, "'"))
        {
            if (IsString)
            {
                Toks.push_back(String[StrIdx]);
                IsString = false;
                StrIdx++;
            }

            else IsString = true;

            NoSpaceLexeme = Lexemes.substr(0, Lexemes.size() - 1);
            if (!Collections::String::IsEmpty(NoSpaceLexeme)) Toks.push_back(NoSpaceLexeme);
            Lexemes = "";
        }

        else if (Strings::Endswith(Lexemes, "(") || Strings::Endswith(Lexemes, ")"))
        {
            NoSpaceLexeme = Lexemes.substr(0, Lexemes.size() - 1);
            if (!Collections::String::IsEmpty(NoSpaceLexeme)) Toks.push_back(NoSpaceLexeme);
            Toks.push_back(Strings::ToString(NonStringStr[i]));
            Lexemes = "";
        }

        if (i == NonStringStr.size() - 1 && !Collections::String::IsEmpty(Lexemes))
        {
            Toks.push_back(Lexemes);
            Lexemes = "";
        }

        Tokens = Toks;
    }

    vector<string> Test = Collections::Array::Reduce(Tokens);
    for (int i = 0; i < Test.size(); i++)
        cout << "[" << Test[i] << "]\n";
}
