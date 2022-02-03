#include "../includes/Glass.h"

// Set console color.
void ConsoleColor::SetConsoleColor(WORD Color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}

// Reset console color.
void ConsoleColor::ResetColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

// Check whether a Phrase exists in Glass's string.
bool InString::IsInString(const string& Line, const string& Phrase, const bool& ExcludeString)
{
    if (ExcludeString)
    {
        string NonStringData = InString::ExcludeDataInString(Line);
        if (Contains(NonStringData, Phrase)) return true;
        else return false;
    }

    else
    {
        string InStringData = InString::DataInString(Line);
        if (Contains(InStringData, Phrase)) return true;
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

// Unrecognized syntax.
void Error::Syntax(const string& details)
{
    ConsoleColor::SetConsoleColor(12);
    cout << "Error!" << endl;
    cout << "Exception Caught at Line " << Count << ",\n" << CurrentLine << endl;
    cout << "\nSyntaxError: " << details << endl;

    ConsoleColor::ResetColor();
    exit(0);
}

// Division by 0.
void Error::ZeroDivision()
{
    ConsoleColor::SetConsoleColor(12);
    cout << "Error!" << endl;
    cout << "Exception Caught at Line " << Count << ",\n" << CurrentLine << endl;
    cout << "ZeroDivisionError: Division by 0" << endl;

    ConsoleColor::ResetColor();
    exit(0);
}

// Unrecognized file format.
void Error::FileFormat()
{
    ConsoleColor::SetConsoleColor(12);
    cout << "Error!" << endl;
    cout << Arguments[0] << ": File not recognized: File format not recognized" << endl;

    ConsoleColor::ResetColor();
    exit(0);
}

// Cannot open file.
void Error::OpenFile()
{
    ConsoleColor::SetConsoleColor(12);
    cout << "Error!" << endl;
    cout << Arguments[0] << ": No such file or directory." << endl;

    ConsoleColor::ResetColor();
    exit(0);
}
