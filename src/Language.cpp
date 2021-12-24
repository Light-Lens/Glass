// Glass.h has all required includes for Glass.
#include "../includes/Glass.h"

// Generate error messages on syntax errors.
void Error(const string& ErrorType)
{
    setConsoleColor(04);
    cout << "Error!" << endl;

    // Unrecognized file format
    if (ErrorType == "FileFormat")
        cout << Arguments[0] << ": File not recognized: File format not recognized" << endl;

    // Cannot open file
    else if (ErrorType == "OpenFile")
        cout << Arguments[0] << ": No such file or directory." << endl;

    // Unrecognized syntax error
    else if (ErrorType == "SyntaxError")
    {
        cout << "Exception Caught at Line " << Count << "," << endl;
        cout << CurrentLine << endl;
    }

    // Unrecognized exception
    else cout << "Unrecognized Exception" << endl;

    setConsoleColor(7);
    exit(0);
}

// Change the Color of the Current Line in Console.
void setConsoleColor(WORD Color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}
