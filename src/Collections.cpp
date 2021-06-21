// All these includes will be used in Glass
#include "../include/Glass.h"

using namespace std; // This will help us not to write std:: multiple times

// This function will format the Equals symbol,
// Because then variables can be created with any style.
std::string Format_Equalsymbol(const std::string Line, const int WhatTODO)
{
    /* WhatTODO int list.
        0 - Return Equalsymbol variable.
        1 - Return repl variable.
    */

    string repl;
    string Equalsymbol;
    if (StrFind(Line, " = "))
    {
        Equalsymbol = " = ";
        repl = replace(Line, "\\" + Equalsymbol, " ");
    }

    else if (StrFind(Line, "= "))
    {
        Equalsymbol = "= ";
        repl = replace(Line, "\\" + Equalsymbol, " ");
    }

    else if (StrFind(Line, " ="))
    {
        Equalsymbol = " =";
        repl = replace(Line, "\\" + Equalsymbol, " ");
    }

    else if (StrFind(Line, "="))
    {
        Equalsymbol = "=";
        repl = replace(Line, "\\" + Equalsymbol, " ");
    }

    if (WhatTODO == 0) return Equalsymbol;
    else return repl;
}

// This function will be used to fetch the actual content.
std::string DataTypeStr(const std::string lines)
{
    // Create some variable which will replace all the syntax words.
    string repl = replace(lines, "string ", "");
    string repl2 = replace(repl, "\\;", "");
    string repl3 = Format_Equalsymbol(repl2, 1);
    string repl4 = replace(repl3, "\"", "");

    // Check whether '=' is given in Line or not.
    // And if '=' is not given then throw an Error.
    if (StrFind(repl2, Format_Equalsymbol(repl2, 0)))
    {
        // Split the string and create "name" and "data" variable.
        auto name = repl3.substr(0, repl3.find(' '));
        auto data = repl3.substr(name.size() + 1, name.find(' '));
        if (getString(data, "\"", "\""))
        {
            // Replace new line with an empty char and return the value.
            string repl5 = replace(repl4, "\n", "");
            return repl5;
        }

        else if (getString(data, "Get(", ")") && Syspart == 1)
        {
            // This piece of code will take input using the ConsoleGet function and and store the data in a variable.
            string Input = ConsoleGet(data); // Calling this function to print the content provided in brakects.
            getline(cin, Input); // Taking input from the user.

            // Process the raw data to join it and make return the processed data. 
            string TitleVal = join(name, " ");
            string GetValue = join(TitleVal, Input);
            string repl5 = replace(GetValue, "\n", "");

            return repl5;
        }

        else if (data == "Time.Now()" && Postpart == 1)
        {
            // This piece of code will call the PostThreadNow function to get the current time.
            string Currenttime = PostThreadNow();

            // Process the raw data to join it and make return the processed data. 
            string TitleVal = join(name, " ");
            string GetValue = join(TitleVal, Currenttime);
            string repl4 = replace(GetValue, "\n", "");

            return repl4;
        }

        else if (getString(data, "System.argv[", "]") && Syspart == 1)
        {
            // This piece of code will call the SystemArgv function to get all the command-line arguments.
            string ARGV = SystemArgv(data); // Calling this function to fetch the actual content.

            // Process the raw data to join it and make return the processed data. 
            string TitleVal = join(name, " ");
            string argvValue = join(TitleVal, Arguments[stoi(ARGV)]);
            string repl5 = replace(argvValue, "\n", "");

            return repl5;
        }

        else if (getString(data, "System.Environment[", "]") && Syspart == 1)
        {
            // This piece of code will call the SystemEnviron function to get access to all the environment variables.
            string Environ = SystemEnviron(data); // Calling this function to fetch the actual content.
            int EnvironmentSize = Environ.length(); // This variable will give the length of variable "Environ".
            char GetEnviron[EnvironmentSize + 1]; /* This will create an empty character array,
            size of Environment size variable.*/

            strcpy(GetEnviron, Environ.c_str()); // Converting String to Const Char*
            char* GetEnviron2 = getenv(GetEnviron); // Getting the value from Environment variable.

            string GetEnvironment; // Creating a string varible named "GetEnvironment".
            GetEnvironment += GetEnviron2; // Add all the chars to "GetEnvironment" variable to convert it to a string.

            // Process the raw data to join it and make return the processed data. 
            string TitleVal = join(name, " ");
            string argvValue = join(TitleVal, GetEnvironment);
            string repl5 = replace(argvValue, "\n", "");

            return repl5;
        }

        else if (getString(data, "\'", "\'") || getString(data, "\"", "\'") || getString(data, "\'", "\"") || startswith(data, "\"") == false || endswith(data, "\"") == false)
        {
            // Throw Error in Exceptions
            Error(lines, to_string(Count));
            return "None";
        }

        else
        {
            // Throw Error in Exceptions
            Error(lines, to_string(Count));
            return "None";
        }
    }

    else
    {
        // Throw Error in Exceptions
        Error(lines, to_string(Count));
        return "None";
    }
}

// This function will be used to fetch the actual content.
std::string DataTypeInt(const std::string lines)
{
    // Create some variable which will replace all the syntax words.
    string return_val;
    string repl = replace(lines, "int ", "");
    string repl2 = replace(repl, "\\;", "");
    string repl3 = Format_Equalsymbol(repl2, 1);

    // Check whether '=' is given in Line or not.
    // And if '=' is not given then throw an Error.
    if (StrFind(repl2, Format_Equalsymbol(repl2, 0)))
    {
        // Split the string and create "name" and "data" variable.
        auto name = repl3.substr(0, repl3.find(' '));
        auto data = repl3.substr(name.size() + 1, name.find(' '));
        if (getString(data, "Random.range(", ")") && Genericpart == 1)
        {
            // This piece of code will call the RandomRange function to get a random whole number.
            string Num = RandomRange(data); // Calling this function to get a random whole number.

            // Process the raw data to join it and make return the processed data. 
            string TitleVal = join(name, " ");
            string GetValue = join(TitleVal, Num);
            string repl4 = replace(GetValue, "\n", "");

            return_val = repl4;
        }

        else if (getString(data, "\"", "\"") == false)
        {
            string repl4 = replace(repl3, "\n", ""); // Replace new line with an empty char.

            /*This For Loop will find the length of the variable "data" and repeat until it's over.
            This Loop will also check whether the Char is a digit or not, and if it's not then just
            throw an Error.*/
            for (int i = 0; i < data.length(); i++)
            {
                if (isdigit(data[i])) return_val = repl4;
                else
                {
                    // Throw Error in Exceptions
                    Error(lines, to_string(Count));
                    return_val = "None";
                }
            }
        }

        else if (getString(data, "\'", "\'") || getString(data, "\"", "\'") || getString(data, "\'", "\"") || startswith(data, "\"") == false || endswith(data, "\"") == false)
        {
            // Throw Error in Exceptions
            Error(lines, to_string(Count));
            return_val = "None";
        }

        else
        {
            // Throw Error in Exceptions
            Error(lines, to_string(Count));
            return_val = "None";
        }
    }

    else
    {
        // Throw Error in Exceptions
        Error(lines, to_string(Count));
        return_val = "None";
    }

    return return_val;
}

// This function will be used to fetch the actual content.
std::string DataTypeFloat(const std::string lines)
{
    // Create some variable which will replace all the syntax words.
    string return_val;
    string repl = replace(lines, "float ", "");
    string repl2 = replace(repl, "\\;", "");
    string repl3 = Format_Equalsymbol(repl2, 1);

    // Check whether '=' is given in Line or not.
    // And if '=' is not given then throw an Error.
    if (StrFind(repl2, Format_Equalsymbol(repl2, 0)))
    {
        // Split the string and create "name" and "data" variable.
        auto name = repl3.substr(0, repl3.find(' '));
        auto data = repl3.substr(name.size() + 1, name.find(' '));
        if (getString(data, "Random.Uniform(", ")") && Genericpart == 1)
        {
            // This piece of code will call the RandomRange function to get a random decimal number.
            string Num = RandomUniform(data); // Calling this function to get a random decimal number.

            // Process the raw data to join it and make return the processed data.
            string TitleVal = join(name, " ");
            string GetValue = join(TitleVal, Num);
            string repl4 = replace(GetValue, "\n", "");

            return_val = repl4;
        }

        else if (getString(data, "Random.range(", ")") && Genericpart == 1)
        {
            // This piece of code will call the RandomRange function to get a random whole number.
            string Num = RandomRange(data); // Calling this function to get a random whole number.

            // Process the raw data to join it and make return the processed data.
            string TitleVal = join(name, " ");
            string GetValue = join(TitleVal, Num);
            string repl4 = replace(GetValue, "\n", "");

            return_val = repl4;
        }

        else if (getString(data, "\"", "\"") == false)
        {
            string repl4 = replace(repl3, "\n", ""); // Replace new line with an empty char.

            /*This For Loop will find the length of the variable "data" and repeat until it's over.
            This Loop will also check whether the Char is a digit or not, and if it's not then it will check
            whether there is '.' in data, else throw an Error.*/
            for (int i = 0; i < data.length(); i++)
            { 
                if (isdigit(data[i])) return_val = repl4;
                else
                {
                    if (data[i] == '.') return_val = repl4;
                    else
                    {
                        // Throw Error in Exceptions
                        Error(lines, to_string(Count));
                        return_val = "None";
                    }
                }
            }
        }

        else if (getString(data, "\'", "\'") || getString(data, "\"", "\'") || getString(data, "\'", "\"") || startswith(data, "\"") == false || endswith(data, "\"") == false)
        {
            // Throw Error in Exceptions
            Error(lines, to_string(Count));
            return_val = "None";
        }

        else
        {
            // Throw Error in Exceptions
            Error(lines, to_string(Count));
            return_val = "None";
        }
    }

    else
    {
        // Throw Error in Exceptions
        Error(lines, to_string(Count));
        return_val = "None";
    }

    return return_val;
}

// This function will be used to fetch the actual content.
std::string DataTypeBool(const std::string lines)
{
    // Create some variable which will replace all the syntax words.
    string repl = replace(lines, "bool ", "");
    string repl2 = replace(repl, "\\;", "");
    string repl3 = Format_Equalsymbol(repl2, 1);

    // Check whether '=' is given in Line or not.
    // And if '=' is not given then throw an Error.
    if (StrFind(repl2, Format_Equalsymbol(repl2, 0)))
    {
        // Split the string and create "name" and "data" variable.
        auto name = repl3.substr(0, repl3.find(' '));
        auto data = repl3.substr(name.size() + 1, name.find(' '));
        if (getString(repl3, "\"", "\"") == false && data == "True")
        {
            // If "data" variable value to "True" then set and return the variable.
            string GetValue = join(name, " True");
            string repl4 = replace(GetValue, "\n", "");

            return repl4;
        }

        else if (getString(repl3, "\"", "\"") == false && data == "False")
        {
            // If "data" variable value to "False" then set and return the variable.
            string GetValue = join(name, " False");
            string repl4 = replace(GetValue, "\n", "");

            return repl4;
        }

        else if (getString(data, "\'", "\'") || getString(data, "\"", "\'") || getString(data, "\'", "\""))
        {
            // Throw Error in Exceptions
            Error(lines, to_string(Count));
            return "None";
        }

        else
        {
            // Throw Error in Exceptions
            Error(lines, to_string(Count));
            return "None";
        }
    }

    else
    {
        // Throw Error in Exceptions
        Error(lines, to_string(Count));
        return "None";
    }
}
