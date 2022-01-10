// Language.h will contain the Lexer and Parser for Glass.
#pragma once

// Glass.h has all required includes for Glass.
#include "../includes/Glass.h"

// Error and Change Console Color function.
void setConsoleColor(WORD Color);
void Error(const string& ErrorType);

// Manager class
struct Manager
{
	// Command-Line arguments manager.
	// Copy paste the command line arguments to an array, and exclude the first item 'Glass.exe' from arguments.
	static vector<string> Command_Line_Argv(int argc, char const *argv[])
	{
		vector<string> Command_Lines;
	    Command_Lines.resize(argc-1);

	    for (int args = 1; args < argc; args++)
	    	Command_Lines[args-1] = argv[args];

	    return Command_Lines;
	}

	// Set all the Packages call value to false.
	static void SetPackagesToDefault()
	{
        vector<string> StandardPackages = {
            "System",
            "Webbrowser",
            "Random",
            "Time",
			"Mathf"
        };

        for (int i = 0; i < StandardPackages.size(); i++)
            Packages[StandardPackages[i]] = false;
	}

	// Check and remove comments.
	static string CheckComments(const string& Line)
	{
		string NewStr = "";
		bool String, Char = false;
		for (int i = 0; i < Line.size(); i++)
		{
			if (Line[i] == '"' && !(Char && Comments))
			{
				if (String) String = false;
				else if (!String) String = true;
			}

			else if (Line[i] == '\'' && !(String && Comments))
			{
				if (Char) Char = false;
				else if (!Char) Char = true;
			}

			else if (Line.substr(i, 2) == "//" && !(String && Char && Comments)) break;
			else if (Line.substr(i, 2) == "/*" && !(String && Char && Comments)) Comments = true;
			else if (Line.substr(i, 2) == "*/" && Comments && !(String && Char)) Comments = false;

			if (!Comments) NewStr += Line[i];
		}

		// TODO: It works for now but further improve it.
		if (Startswith(NewStr, "*/")) NewStr = NewStr.substr(2);
		return NewStr;
	}

	// Check for any irregularities in line.
	static int BracketsNQuotes(const string& Line, const string& Sw, const string& Ew)
	{
		// Sw   -> Startswith
		// Ew   -> Endsswith
		if (Sw == Ew)
		{
			const int StartCount = StrCount(Line, Sw);
			if (StartCount != 0)
			{
				if (IsEven(StartCount)) return 1;
				else return 0;
			}
		}

		else
		{
			const int StartCount = StrCount(Line, Sw);
			const int EndCount = StrCount(Line, Ew);
			if (StartCount != 0 || EndCount != 0)
			{
				if (StartCount == EndCount) return 1;
				else return 0;
			}
		}

		return -1;
	}
};

// Language class
class Lang
{
private:
	// Tokenize a syntax by splitting key and value.
	vector<string> Tokenize(const string& FullString, const string& SubString)
	{
		vector<string> Tokens = Split(FullString, SubString, true);
		return Tokens;
	}

	// MAKE VALUES READABLE.
	// 'Index2Of_FS' stands for 'Index 2 of Formatted String (FormattedString[1])',
	// 'Sw' and 'Ew' stands for 'Startswith' and 'Endswith' respectively.
	string ConvertToReadableFormat(const string& Index2Of_FS, const string& Sw, const string& Ew)
	{
		string New_ReadableString = Index2Of_FS;
		New_ReadableString.resize(2);

		if (Startswith(Index2Of_FS, Sw) && Endswith(Index2Of_FS, Ew))
			New_ReadableString = Index2Of_FS.substr(1, Index2Of_FS.size()-2);

		return New_ReadableString;
	}

public:
    Lang(const string& OriginalLine)
    {
		string Line = Manager::CheckComments(OriginalLine);
		if (!Line.empty())
		{
			// IF ANY LINE ENDSWITH A SEMICOLON REMOVE ';' FROM THE LINE.
			if (Endswith(Line, ";")) Line = Trim(ReplaceLast(Line, ";", ""));

			// Check for incorrect quotes and brackets.
			if (Manager::BracketsNQuotes(Line, "(", ")") == 0) Error("SyntaxError");
			if (Manager::BracketsNQuotes(Line, "[", "]") == 0) Error("SyntaxError");
			if (Manager::BracketsNQuotes(Line, "\"", "\"") == 0)
			{
				if (Manager::BracketsNQuotes(Line, "'", "'") == 0) Error("SyntaxError");
			}

			// PERFORM SOME LEXICAL ANALYSIS.
			vector<string> Tokens = Lexer(Line);
			Tokens[1] = Collections::DataTypes(Tokens[1]); // Classify all datatypes.

			// Parse the Tokens.
			Parse(Tokens);
		}
    }

	vector<string> Lexer(const string& Line)
	{
		bool String, Char = false;
		vector<string> Tokens;
		Tokens.resize(2);

		// Tokenize the functions, arrays and variables.
		for (int i = 0; i < Line.size(); i++)
		{
			if (Line[i] == '"' && !Char)
			{
				if (String) String = false;
				else if (!String) String = true;
			}

			else if (Line[i] == '\'' && !String)
			{
				if (Char) Char = false;
				else if (!Char) Char = true;
			}

			else if (Line[i] == '=' && !String && !Char)
			{
				Tokens = Tokenize(Line, "=");

				Tokens[0] = "VAR:" + Tokens[0];
				Tokens[1] = Trim(ReplaceFirst(Tokens[1], "=", ""));
				break;
			}

			else if (Line[i] == '(' && !String && !Char)
			{
				Tokens = Tokenize(Line, "(");

				Tokens[0] = "FUN:" + Tokens[0];
				Tokens[1] = ConvertToReadableFormat("(" + Tokens[1], "(", ")");
				break;
			}

			else if (Line[i] == '[' && !String && !Char)
			{
				Tokens = Tokenize(Line, "[");

				Tokens[0] = "ARR:" + Tokens[0];
				Tokens[1] = ConvertToReadableFormat("[" + Tokens[1], "[", "]");
				break;
			}

			else if (i >= Line.size()-1)
			{
				Tokens = Tokenize(Line, "");
				break;
			}
		}

		return Tokens;
	}

	/* Classification of Functional Keywords.
		ARR   -> Array
		VAR   -> Variable
		FUN   -> Function */
	// Parse all the Line and give out some output in accordance to that Line.
	void Parse(const vector<string>& FormattedLine)
	{
        // THIS PACKAGE MANAGER WILL KEEP TRACK OF ALL CURRENTLY IN-USE PACKAGES.
		if (FormattedLine[0] == "import" && Packages.count(FormattedLine[1]) > 0) Packages[FormattedLine[1]] = true;

		// THESE IF STATEMENTS WILL BE USED FOR VARIABLES DECLARATION AND USAGE.
		else if (FormattedLine[0] == "FUN:Type") GetVarType(FormattedLine[1]);
		else if (Startswith(FormattedLine[0], "VAR:")) DeclareVar(FormattedLine);

		// Use Standard functions without importing any package.
		else if (FormattedLine[0] == "FUN:Shout") Shout(FormatToRun(FormattedLine[1], {"STR", "INT", "FLOAT", "BOOL", "ARR", "None"}));
		else if (FormattedLine[0] == "FUN:Shoutln") Shoutln(FormatToRun(FormattedLine[1], {"STR", "INT", "FLOAT", "BOOL", "ARR", "None"}));
		else if (FormattedLine[0] == "FUN:Get") Get(FormatToRun(FormattedLine[1], {"STR", "INT", "FLOAT", "BOOL", "ARR", "None"}));
		else if (FormattedLine[0] == "FUN:GetKey") GetKey(FormatToRun(FormattedLine[1], {"STR", "INT", "FLOAT", "BOOL", "ARR", "None"}));

		// Import System Package.
		else if (FormattedLine[0] == "FUN:System.Exit" && Packages["System"]) SystemExit(stoi(FormatToRun(FormattedLine[1], {"INT"})));
		else if (FormattedLine[0] == "FUN:Console.CMD" && Packages["System"]) ConsoleCMD(FormatToRun(FormattedLine[1], {"STR"}));
		else if (FormattedLine[0] == "ARR:System.Argv" && Packages["System"]) SystemArgv(stoi(FormatToRun(FormattedLine[1], {"INT"})));
		else if (FormattedLine[0] == "ARR:System.Environment" && Packages["System"]) SystemEnviron(FormatToRun(FormattedLine[1], {"STR"}));

		// Import Time Package.
		else if (FormattedLine[0] == "FUN:Time.Sleep" && FormattedLine[1] == "None" && Packages["Time"]) Sleep(stof(FormatToRun(FormattedLine[1], {"INT", "FLOAT"})));
		else if (FormattedLine[0] == "FUN:Time.Now" && FormattedLine[1] == "None" && Packages["Time"]) TimeNow();
		else if (FormattedLine[0] == "FUN:Time.Now.OnlyTime" && FormattedLine[1] == "None" && Packages["Time"]) OnlyTime();
		else if (FormattedLine[0] == "FUN:Time.Now.Minute" && FormattedLine[1] == "None" && Packages["Time"]) Min();
		else if (FormattedLine[0] == "FUN:Time.Now.Second" && FormattedLine[1] == "None" && Packages["Time"]) Sec();
		else if (FormattedLine[0] == "FUN:Time.Now.Hour" && FormattedLine[1] == "None" && Packages["Time"]) Hour();
		else if (FormattedLine[0] == "FUN:Time.Now.Date" && FormattedLine[1] == "None" && Packages["Time"]) Date();
		else if (FormattedLine[0] == "FUN:Time.Now.Year" && FormattedLine[1] == "None" && Packages["Time"]) Year();
		else if (FormattedLine[0] == "FUN:Time.Now.Month" && FormattedLine[1] == "None" && Packages["Time"]) Month();
		else if (FormattedLine[0] == "FUN:Time.Now.DayOfWeek" && FormattedLine[1] == "None" && Packages["Time"]) DayOfWeek();
		else if (FormattedLine[0] == "FUN:Time.Now.DayInMonth" && FormattedLine[1] == "None" && Packages["Time"]) DayInMonth();
		else Error("SyntaxError");
	}
};
