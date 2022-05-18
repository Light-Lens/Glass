#include "..\includes\Common.h"
using namespace std;

// Unrecognized syntax.
// void Error::Syntax(const string& details)
// {
//     ConsoleColor::SetConsoleColor(12);
//     cout << "Error!" << endl;
//     cout << "Exception Caught at Line " << Count << ",\n" << CurrentLine << endl;
//     cout << "\nSyntaxError: " << details << endl;

//     ConsoleColor::ResetColor();
//     exit(0);
// }

// // Division by 0.
// void Error::ZeroDivision()
// {
//     ConsoleColor::SetConsoleColor(12);
//     cout << "Error!" << endl;
//     cout << "Exception Caught at Line " << Count << ",\n" << CurrentLine << endl;
//     cout << "ZeroDivisionError: Division by 0" << endl;

//     ConsoleColor::ResetColor();
//     exit(0);
// }

// Unrecognized file format.
void Error::FileFormat(string Filename)
{
    ConsoleColor::SetConsoleColor(12);
    cout << "Error!" << endl;
    cout << Filename << ": File not recognized: File format not recognized" << endl;

    ConsoleColor::ResetColor();
    exit(0);
}

// Cannot open file.
void Error::OpenFile(string Filename)
{
    ConsoleColor::SetConsoleColor(12);
    cout << "Error!" << endl;
    cout << Filename << ": No such file or directory." << endl;

    ConsoleColor::ResetColor();
    exit(0);
}
