// Glass.h has all required includes for Glass.
#include "../includes/Glass.h"

// Change the Color of the Current Line in Console.
struct ConsoleColor
{
    static void SetConsoleColor(WORD Color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
    }

    static void ResetColor()
    {
        WORD Color = 7;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
    }
};

// TODO: Add more Error messages.
// Unrecognized syntax
void Error::SyntaxError()
{
    ConsoleColor::SetConsoleColor(04);
    cout << "Error!" << endl;
    cout << "Exception Caught at Line " << Count << ",\n" << CurrentLine << endl;

    ConsoleColor::ResetColor();
    exit(0);
}

// Unrecognized file format
void Error::FileFormat()
{
    ConsoleColor::SetConsoleColor(04);
    cout << "Error!" << endl;
    cout << Arguments[0] << ": File not recognized: File format not recognized" << endl;

    ConsoleColor::ResetColor();
    exit(0);
}

// Cannot open file
void Error::OpenFile()
{
    ConsoleColor::SetConsoleColor(04);
    cout << "Error!" << endl;
    cout << Arguments[0] << ": No such file or directory." << endl;

    ConsoleColor::ResetColor();
    exit(0);
}
