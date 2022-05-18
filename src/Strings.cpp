#include "..\includes\Common.h"
using namespace std;

// =========================================
//                InStrings
// =========================================

// Check whether a Phrase exists in Glass's string.
bool InString::IsInString(const string& Line, const string& Phrase, const bool& ExcludeString)
{
    if (ExcludeString)
    {
        string NonStringData = InString::ExcludeDataInString(Line);
        if (Strings::Find(NonStringData, Phrase)) return true;
        else return false;
    }

    else
    {
        string InStringData = InString::DataInString(Line);
        if (Strings::Find(InStringData, Phrase)) return true;
        else return false;
    }

    return false;
}

// Extract all the data from a string.
string InString::DataInString(const string& Line)
{
    char StrQuote = '\0';
    bool EscapeChar = false;
    string InStringData = "";

    // Loop over every char and store those which exist in In-Glass String.
    for (const char& i : Line)
    {
		if (i == '"' && !EscapeChar)
		{
            InStringData += i;
            if (StrQuote == '\0') StrQuote = '"';
            else if (StrQuote == '"') StrQuote = '\0';
		}

		else if (i == '\'' && !EscapeChar)
		{
            InStringData += i;
            if (StrQuote == '\0') StrQuote = '\'';
            else if (StrQuote == '\'') StrQuote = '\0';
		}

        else if (StrQuote != '\0') InStringData += i;

        if (i == '\\' && StrQuote != '\0') EscapeChar = true;
        else if (EscapeChar) EscapeChar = false;
    }

    return InStringData;
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

        if (i == '\\' && StrQuote != '\0') EscapeChar = true;
        else if (EscapeChar) EscapeChar = false;
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
