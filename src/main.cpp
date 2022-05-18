#include "../includes/Common.h"
using namespace std;

int main(int argc, char const *argv[])
{
    // Initializing Glass
    fstream File;
    vector<string> Arguments = Manager::ArgParse(argc, argv);

    int LineNum = 0;
    string CurrentLine;

    if (Arguments.size() == 0)
    {
        // Show Glass version.
        ConsoleColor::SetConsoleColor(14);
        cout << "Glass 2022 [Version 1.3]";
        ConsoleColor::ResetColor();

        // Run forever.
        while (true)
        {
            LineNum++; // +1 on every new line.

            // Take input.
            cout << "\n> ";
            getline(cin, CurrentLine);
            cout << "Hello world!" << endl;
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
                while (getline(File, CurrentLine))
                {
                    LineNum++; // +1 on every new line.
                    cout << "Hello world!" << endl;
                }

                // Close the file.
                File.close();
            }
        }
    }

    return 0;
}
