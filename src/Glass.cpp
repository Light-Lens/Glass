// Glass programming language
// All these includes will be used in Glass
#include "../include/Glass.h"

using namespace std; // This will help us not to write std:: multiple times

// These are the Glass variable dictionaries
std::map<std::string, std::string> variables;
std::map<std::string, std::string> VarTypes;

// Package manager.
int Syspart;
int Cgrpart;
int Postpart;
int Webbrowser;
int FileIOpart;
int Genericpart;
int Collectionpart;

int Count; // This will make Count variable global which will be used by Error function.
int Comments; /* This will make Comments variable global,
which will be used to check whether there is a multiline comment in the code.*/

std::string Arguments[7000]; // You can change this in FUTURE.

/* This is a global function which will generate error messages on syntax errors.
Make this Error message function more dynamic in future.*/
void Error(const std::string lines, const std::string num)
{
    setConsoleColor(04);
    cout << "Error.\nException Caught at Line: " << num << endl << "Exceptional Line: " << lines;
    setConsoleColor(7);
    exit(0);
}

// Main function for Glass, all the main syntax calling will be done here only.
int main(int argc, char** argv)
{
    // Global variables
    fstream in;
    string Line;
    string DirName;
    Count = 0;

    // Initializing Glass
    DirName = argv[1]; /* Reading command-line index[1] argument and saving it to DirName variable.
    This variable will be used to check whether the filename is given in proper form or not.*/
    if (endswith(DirName, ".glass")) in.open(DirName); // Opening .glass file if the filename is proper in DirName variable.
    else
    {
        /* Throwing an error message saying "Cannot read the file!", and stop the program.
        You must make this message more dynamic while adding other command-line arguments.*/
    	setConsoleColor(04);
    	cout << "Error.\nCannot read \"" << DirName << "\"" << endl;
        setConsoleColor(7);
    	exit(0);
    }

    // Package manager.
    Syspart = 0;
    Cgrpart = 0;
    Postpart = 0;
    FileIOpart = 0;
    Webbrowser = 0;
    Genericpart = 0;
    Collectionpart = 0;

    // Comments and Arguments manager.
    Comments = 0;
    for (int argus = 0; argus < argc; argus++) Arguments[argus] = argv[argus];

    /* This While Loop will run until the file is reached at it's end,
    and it will also check certain conditions to make the programming language working properly.*/
    while (in)
    {
        Count++; // +1 to Count variable to get the number of lines executed.
        getline(in, Line);

        /* These are not part of any Package.
        These are just default program syntax which doesn't need any Package to be imported to call.*/
        if (Line == "" || Line == " " || startswith(Line, "  ")) continue;
        else if (startswith(Line, "//")) continue;
        else if (getString(Line, "/*", "*/")) continue;
        else if (startswith(Line, "/*") && Comments == 0) Comments = 1;
        else if (endswith(Line, "*/") && Comments == 1) Comments = 0;

        /* These are the Package caller. This package will check that which package is imported,
        on that basis the other package functions will work.*/
        else if (Line == "using System;" && Comments == 0) Syspart = 1;
        else if (Line == "using FileIO;" && Comments == 0) FileIOpart = 1;
        else if (Line == "using Generic;" && Comments == 0) Genericpart = 1;
        else if (Line == "using PostThread;" && Comments == 0) Postpart = 1;
        else if (Line == "using Webbrowser;" && Comments == 0) Webbrowser = 1;
        else if (Line == "using Cgr.Graphics;" && Comments == 0) Cgrpart = 1;
        else if (Line == "using Collections.DataTypes;" && Comments == 0) Collectionpart = 1;

        // These are the part of the System Package.
        else if (Line == "System.Exit();" && Syspart == 1 && Comments == 0) exit(0);
        else if (Line == "Console.Clear();" && Syspart == 1 && Comments == 0) ConsoleClear();
        else if (getString(Line, "Console.CMD(", ");") && Syspart == 1 && Comments == 0) ConsoleCMD(Line);
        else if (getString(Line, "Console.Title(", ");") && Syspart == 1 && Comments == 0) ConsoleTitle(Line);
        else if (getString(Line, "Console.Color(", ");") && Syspart == 1 && Comments == 0) ConsoleColor(Line);
        else if (getString(Line, "Shout(", ");") && Syspart == 1 && Comments == 0) ConsoleShout(Line);
        else if (getString(Line, "Shoutln(", ");") && Syspart == 1 && Comments == 0) ConsoleShoutln(Line);
        else if (getString(Line, "Get(", ");") && Syspart == 1 && Comments == 0)
        {
            string Input = ConsoleGet(Line); // Calling this function to print the content provided in brakects.
            getline(cin, Input); // Taking input from the user.
        }

        else if (getString(Line, "GetKey(", ");") && Syspart == 1 && Comments == 0)
        {
            ConsoleGetKey(Line); // Calling this function to print the content provided in brakects.
            getch(); // Wating for a key to be pressed on the keyboard.
        }

        else if (getString(Line, "System.argv[", "];") && Syspart == 1 && Comments == 0)
        {
            string ARGV = SystemArgv(Line); // Calling this function to fetch the actual content.
            Arguments[stoi(ARGV)]; // Getting command-line argument
        }

        else if (getString(Line, "System.Environment[", "];") && Syspart == 1 && Comments == 0)
        {
            string Environ = SystemEnviron(Line); // Calling the this function to fetch the actual content.
            int EnvironmentSize = Environ.length(); // This variable will give the length of variable "Environ".
            char GetEnvironment[EnvironmentSize + 1]; /* This will create an empty character array,
            size of Environment size variable.*/

            strcpy(GetEnvironment, Environ.c_str()); // Converting String to Const Char*
            getenv(GetEnvironment); // Getting the value from Environment variable.
        }

        // These are the part of PostThread Package.
        else if (getString(Line, "Time.Sleep(", ");") && Postpart == 1 && Comments == 0) PostThreadSleep(Line);
        else if (Line == "Time.Now();" && Postpart == 1 && Comments == 0) PostThreadNow();

        // These are the part of the Generic Package.
        else if (getString(Line, "Random.range(", ");") && Genericpart == 1 && Comments == 0) RandomRange(Line);
        else if (getString(Line, "Random.Uniform(", ");") && Genericpart == 1 && Comments == 0) RandomUniform(Line);

        // These are the part of Collections Package.
        else if (getString(Line, "string ", ";") && Collectionpart == 1 && Comments == 0)
        {
            string Value = DataTypeStr(Line); // Calling the this function to fetch the actual content.
            string Type = "type<string>"; // This variable will set declare a string datatype.

            auto Title = Value.substr(0, Value.find(' ')); // Get the variable name.
            auto Content = Value.substr(Title.size() + 1, Title.find(' ')); // Get the content of the variable.

            variables[Title] = Content; // Set variable.
            VarTypes[Title] = Type; // Set datatype of the variable.
        }

        else if (getString(Line, "int ", ";") && Collectionpart == 1 && Comments == 0)
        {
            string Value = DataTypeInt(Line); // Calling the this function to fetch the actual content.
            string Type = "type<int>"; // This variable will set declare a int datatype.

            auto Title = Value.substr(0, Value.find(' ')); // Get the variable name.
            auto Content = Value.substr(Title.size() + 1, Title.find(' ')); // Get the content of the variable.

            variables[Title] = Content; // Set variable.
            VarTypes[Title] = Type; // Set datatype of the variable.
        }

        else if (getString(Line, "float ", ";") && Collectionpart == 1 && Comments == 0)
        {
            string Value = DataTypeFloat(Line); // Calling the this function to fetch the actual content.
            string Type = "type<float>"; // This variable will set declare a float datatype.

            auto Title = Value.substr(0, Value.find(' ')); // Get the variable name.
            auto Content = Value.substr(Title.size() + 1, Title.find(' ')); // Get the content of the variable.

            variables[Title] = Content; // Set variable.
            VarTypes[Title] = Type; // Set datatype of the variable.
        }

        else if (getString(Line, "bool ", ";") && Collectionpart == 1 && Comments == 0)
        {
            string Value = DataTypeBool(Line); // Calling the this function to fetch the actual content.
            string Type = "type<boolean>"; // This variable will set declare a bool datatype.

            auto Title = Value.substr(0, Value.find(' ')); // Get the variable name.
            auto Content = Value.substr(Title.size() + 1, Title.find(' ')); // Get the content of the variable.

            variables[Title] = Content; // Set variable.
            VarTypes[Title] = Type; // Set datatype of the variable.
        }

        // This will Catch an Error in the program.
        else
        {
            if (Comments == 0) Error(Line, to_string(Count)); // Throw an error if Comments variable value is 0
            else continue; /* If the Comments variable value is not 0 then ignore the line,
            because it's a multiline comment.*/
        }
    }
    in.close(); // Close the file.
    return 0; // return 0 (It's Important!).
}
