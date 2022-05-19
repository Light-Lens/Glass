#include "..\includes\Common.h"
using namespace std;

string Lexer::TrimmedLine;

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
    cout << TrimmedLine << endl;
}
