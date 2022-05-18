#include "../includes/Common.h"
using namespace std;

int LineNum = 0;
string CurrentLine;

// Run the code.
void run()
{
    LineNum++; // +1 on every new line.
    cout << CurrentLine << endl;
}

// Entry point
int main(int argc, char const *argv[])
{
    // Initializing Glass
    fstream File;
    vector<string> Arguments = Manager::ArgParse(argc, argv);

    if (Arguments.size() == 0)
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
    else if (Arguments.size() > 0)
    {
        if (!Strings::Endswith(Arguments[0], ".glass")) Error::FileFormat(Arguments[0]);
        else
        {
            // Check if file opens properly.
            File.open(Arguments[0]);
            if (!File) Error::OpenFile(Arguments[0]);
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
