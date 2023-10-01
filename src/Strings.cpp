#include "..\includes\Common.h"
using namespace std;

// =========================================
//                InStrings
// =========================================

// Extract all the data from a string.
vector<string> InString::DataInString(const string& Line)
{
    char StrQuote = '\0';
    bool EscapeChar = false;
    string InStringData = "";
    vector<string> Strings;

    // Loop over every char and store those which exist in In-Glass String.
    for (const char& i : Line)
    {
        if (EscapeChar)
        {
            if (i == '\\') InStringData += "\\";

            // Punctuation characters.
            else if (i == '\'') InStringData += "'";
            else if (i == '"') InStringData += "\"";

            // Control characters.
            else if (i == 'n') InStringData += "\n";
            else if (i == 't') InStringData += "\t";
            else if (i == 'b') InStringData += "\b";
            else if (i == 'r') InStringData += "\r";
            else if (i == 'f') InStringData += "\f";
            else if (i == 'v') InStringData += "\v";
            else InStringData += i;

            EscapeChar = false;
        }

        else
        {
            if (i == '"' && !EscapeChar)
            {
                InStringData += i;
                if (StrQuote == '\0') StrQuote = '"';
                else if (StrQuote == '"')
                {
                    StrQuote = '\0';
                    Strings.push_back(InStringData);
                    InStringData = "";
                }
            }

            else if (i == '\'' && !EscapeChar)
            {
                InStringData += i;
                if (StrQuote == '\0') StrQuote = '\'';
                else if (StrQuote == '\'')
                {
                    StrQuote = '\0';
                    Strings.push_back(InStringData);
                    InStringData = "";
                }
            }

            else if (i == '\\' && StrQuote != '\0') EscapeChar = true;
            else if (StrQuote != '\0') InStringData += i;
        }
    }

    return Strings;
}

// Exclude all data in a string.
string InString::ExcludeDataInString(const string& Line)
{
    char StrQuote = '\0';
    bool EscapeChar = false;
    string NonStringData = "";

    // Loop over every char and store those which does not exist in In-Glass String.
    for (const char& i : Line)
    {
        if (i == '"' && !EscapeChar)
        {
            if (StrQuote == '\0')
            {
                StrQuote = '"';
                NonStringData += i;
            }

            else if (StrQuote == '"')
            {
                StrQuote = '\0';
                NonStringData += i;
            }
        }

        else if (i == '\'' && !EscapeChar)
        {
            if (StrQuote == '\0')
            {
                StrQuote = '\'';
                NonStringData += i;
            }

            else if (StrQuote == '\'')
            {
                StrQuote = '\0';
                NonStringData += i;
            }
        }

        else if (StrQuote == '\0') NonStringData += i;

        if (EscapeChar) EscapeChar = false;
        else if (i == '\\' && StrQuote != '\0') EscapeChar = true;
    }

    return NonStringData;
}

// =========================================
//                 Strings
// =========================================

// Check whether a string startswith a particular substring.
bool Strings::Startswith(const string& Sentence, const string& WhatToFind)
{
    if (Sentence.find(WhatToFind) == 0) return true;
    else return false;
}

// Check whether a string endswith a particular substring.
bool Strings::Endswith(const string& Sentence, const string& WhatToFind)
{
    if (Sentence.length() >= WhatToFind.length())
        return (0 == Sentence.compare(Sentence.length() - WhatToFind.length(), WhatToFind.length(), WhatToFind));

    else return false;
}

// Check whether a string exists a particular substring.
bool Strings::Find(const string& Sentence, const string& WhatToFind)
{
    if (Sentence.find(WhatToFind) != string::npos) return true;
    else return false;
}

// Trim a certain char from the staring and ending of a string.
string Strings::Trim(const string& Sentence)
{
    const string Whitespace = " \t";
    const auto strBegin = Sentence.find_first_not_of(Whitespace);
    if (strBegin == string::npos) return "";

    const auto strEnd = Sentence.find_last_not_of(Whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return Sentence.substr(strBegin, strRange);
}

// Check whether the given number is Odd or Even.
bool Strings::IsEven(const int& Number)
{
    return (Number % 2 == 0);
}
