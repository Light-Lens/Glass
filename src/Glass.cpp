// Glass programming language
// Glass.h has all required includes for Glass.
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
    Arguments = Manager::Command_Line_Argv(argc, argv);
    Manager::SetPackagesToDefault();

    // Read the first argument from command-line and save it to Filename variable.
    // This variable will be used to check whether the filename is given in proper form or not.
    // Open ".glass" file.
    if (Endswith(Arguments[0], ".glass")) File.open(Arguments[0]);
    else Error("FileFormat");

    // Check if file opens properly.
    if (!File) Error("OpenFile");
    else
    {
        // Run until the file is reached it's end,
        while (getline(File, CurrentLine))
        {
            // Increment 1 to Count everytime a line is executed.
            Count++;
            Lang Code(CurrentLine);
        }

        // Close the file.
        File.close();
    }

    return 0;
}
