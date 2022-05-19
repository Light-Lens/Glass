#include "..\includes\Common.h"
using namespace std;

int LineNum = 0;
string CurrentLine;

// Run the code.
void run()
{
    LineNum++; // +1 on every new line.
    Lexer lex;
}

// Entry point
int main(int argc, char const *argv[])
{
    // Initializing Glass
    fstream File;
    vector<string> args = Manager::ArgParse(argc, argv);

    if (args.size() == 0)
    {
        // Show Glass version.
        ConsoleColor::SetConsoleColor(14);
        cout << "Glass 2022 [Version 1.3]";
        ConsoleColor::ResetColor();

        // Take input.
        while (true)
        {
            cout << "\n> ";
            getline(cin, CurrentLine);
            run();
        }
    }

    // Read the first argument and save it as a variable.
    else if (args.size() > 0)
    {
        if (!Strings::Endswith(args[0], ".glass")) Error::FileFormat(args[0]);
        else
        {
            // Check if file opens properly.
            File.open(args[0]);
            if (!File) Error::OpenFile(args[0]);
            else
            {
                // Run until the file is reached it's end
                while (getline(File, CurrentLine)) run();
            }

            // Close the file.
            File.close();
        }
    }

    return 0;
}
