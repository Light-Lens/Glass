// Glass programming language
#include "../includes/Glass.h"

// Global variables.
int Count;
bool Comments;

string CurrentLine;
vector<string> Arguments;
map<string, string> Variables;
map<string, bool> Packages;

// Main function.
int main(int argc, char const *argv[])
{
    // Initializing Glass
    fstream File;

    Count = 0;
    Comments = false;
    Arguments = Manager::ArgParse(argc, argv);
    Manager::SetPackagesToDefault();

    if (Arguments.size() == 0)
    {
        // Show GLass version.
        ConsoleColor::SetConsoleColor(14);
        cout << "Glass 2022 [Version 1.2]";
        ConsoleColor::ResetColor();

        // Run forever.
        while (true)
        {
            Count++; // Increment 1 to Count everytime a line is executed.

            // Take input.
            cout << "\n> ";
            getline(cin, CurrentLine);
            Lang Code(CurrentLine);
        }
    }

    // Read the first argument and save it as a variable.
    else if (Arguments.size() > 0)
    {
        if (!Endswith(Arguments[0], ".glass")) Error::FileFormat();
        else
        {
            // Check if file opens properly.
            File.open(Arguments[0]);
            if (!File) Error::OpenFile();
            else
            {
                // Run until the file is reached it's end
                while (getline(File, CurrentLine))
                {
                    Count++; // Increment 1 to Count everytime a line is executed.
                    Lang Code(CurrentLine);
                }

                // Close the file.
                File.close();
            }
        }
    }

    return 0;
}
