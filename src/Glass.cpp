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

int Count; // This will make a global Count variable which will be used by Error function.

// This is a global function which will help to make error messages more dynamic.
void Error(const std::string lines, const std::string num)
{
    system("color 04");
    cout << "Error.\nException Catched at Line: " << num << endl << "Exceptional Line: " << lines;
    exit(0);
}

int main(int argc, char** argv)
{
    // Global variables
    fstream in;
    string Line;
    string DirName;
    Count = 0;

    // Initializing Glass
    DirName = argv[1];
    if (endswith(DirName, ".glass")) in.open(DirName);
    else
    {
    	system("color 04");
    	cout << "Cannot read \"" << DirName << "\"" << endl;
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

    // Main langauge
    while (in)
    {
        Count++;
        getline(in, Line);
        // These are not part of any Package.
        if (Line == "" || Line == " " || startswith(Line, "  ")) continue;
        else if (startswith(Line, "//")) continue;

        // These are the Package caller.
        else if (Line == "using System;") Syspart = 1;
        else if (Line == "using FileIO;") FileIOpart = 1;
        else if (Line == "using Generic;") Genericpart = 1;
        else if (Line == "using PostThread;") Postpart = 1;
        else if (Line == "using Webbrowser;") Webbrowser = 1;
        else if (Line == "using Cgr.Graphics;") Cgrpart = 1;
        else if (Line == "using Collections.DataTypes;") Collectionpart = 1;

        // These are the part of the System Package.
        else if (Line == "System.Exit();" && Syspart == 1) exit(0);
        else if (Line == "Console.Clear();" && Syspart == 1) ConsoleClear();
        else if (getString(Line, "Console.CMD(", ");") && Syspart == 1) ConsoleCMD(Line);
        else if (getString(Line, "Console.Title(", ");") && Syspart == 1) ConsoleTitle(Line);
        else if (getString(Line, "Console.Color(", ");") && Syspart == 1) ConsoleColor(Line);
        else if (getString(Line, "Shout(", ");") && Syspart == 1) ConsoleShout(Line);
        else if (getString(Line, "Shoutln(", ");") && Syspart == 1) ConsoleShoutln(Line);
        else if (getString(Line, "Get(", ");") && Syspart == 1)
        {
            string Input = ConsoleGet(Line);
            getline(cin, Input);
        }

        // These are the part of PostThread Package.
        else if (getString(Line, "Time.Sleep(", ");") && Postpart == 1) PostThreadSleep(Line);

        // These are the part of the Generic Package.
        else if (getString(Line, "Random.rand(", ");") && Genericpart == 1) RandomRange(Line);
        else if (getString(Line, "Random.Uniform(", ");") && Genericpart == 1) RandomUniform(Line);

        // These are the part of Collections Package.
        else if (getString(Line, "string ", ";") && Collectionpart == 1)
        {
            string Value = DataTypeStr(Line);
            string Type = "type<string>";

            auto Title = Value.substr(0, Value.find(' '));
            auto Content = Value.substr(Title.size() + 1, Title.find(' '));

            variables[Title] = Content;
            VarTypes[Title] = Type;
        }

        else if (getString(Line, "int ", ";") && Collectionpart == 1)
        {
            string Value = DataTypeInt(Line);
            string Type = "type<int>";

            auto Title = Value.substr(0, Value.find(' '));
            auto Content = Value.substr(Title.size() + 1, Title.find(' '));

            variables[Title] = Content;
            VarTypes[Title] = Type;
        }

        else if (getString(Line, "float ", ";") && Collectionpart == 1)
        {
            string Value = DataTypeFloat(Line);
            string Type = "type<float>";

            auto Title = Value.substr(0, Value.find(' '));
            auto Content = Value.substr(Title.size() + 1, Title.find(' '));

            variables[Title] = Content;
            VarTypes[Title] = Type;
        }

        else if (getString(Line, "bool ", ";") && Collectionpart == 1)
        {
            string Value = DataTypeBool(Line);
            string Type = "type<boolean>";

            auto Title = Value.substr(0, Value.find(' '));
            auto Content = Value.substr(Title.size() + 1, Title.find(' '));

            variables[Title] = Content;
            VarTypes[Title] = Type;
        }

        // This will Catch an Exceptional error.
        else Error(Line, to_string(Count));
    }
    in.close();
    return 0;
}
