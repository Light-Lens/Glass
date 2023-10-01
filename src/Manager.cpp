#include "..\includes\Common.h"
using namespace std;

// Copy paste all command line arguments to an array except 'Glass.exe'.
vector<string> Manager::ArgParse(int argc, char const *argv[])
{
    vector<string> CommandLines(argv, argv + argc);
    CommandLines.erase(CommandLines.begin());

    return CommandLines;
}

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
