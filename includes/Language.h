// Lexer, Parser and Evaluator for Glass.
#pragma once
#include "../includes/Glass.h"

// Check if a substring is in a string or not.
//* NOTE: The string is In-Glass string.
struct InString
{
	static string DataInString(const string& Line);
	static string ExcludeDataInString(const string& Line);
	static bool IsInString(const string& Line, const string& Phrase, const bool& ExcludeString=false);
};

// Change the Color of the Current Line in Console.
struct ConsoleColor
{
    static void SetConsoleColor(WORD Color);
    static void ResetColor();
};

// Generate error messages.
struct Error
{
	static void Syntax(const string& details="");
	static void ZeroDivision();
	static void FileFormat();
	static void OpenFile();
};

// Manager class
struct Manager
{
    // Copy paste all command line arguments to an array except 'Glass.exe'.
    static vector<string> ArgParse(int argc, char const *argv[])
    {
        vector<string> CommandLines(argv, argv + argc);
        CommandLines.erase(CommandLines.begin());

        return CommandLines;
    }

	// Set all the Packages call value to false.
	static void SetPackagesToDefault()
	{
        vector<string> StandardPackages = {
			"System",
			"String",
			"Time",
			"Random",
			"Mathf",
			"Webbrowser",
			"ArgParse",
			"RegEx",
			"FileIO",
			"Json",
			"GlassUI",
			"Cgr"
        };

        for (int i = 0; i < StandardPackages.size(); i++)
            Packages[StandardPackages[i]] = false;
	}

	// Check and remove comments.
	static string CheckComments(const string& Line)
	{
		char StrQuote = '\0';
		bool EscapeChar = false;
		bool String, Char = false;
		string UnCommentedStr = "";

		for (int i = 0; i < Line.size(); i++)
		{
			if (Line[i] == '"' && !EscapeChar)
			{
				if (StrQuote == '\0') StrQuote = '"';
				else if (StrQuote == '"') StrQuote = '\0';
			}

			else if (Line[i] == '\'' && !EscapeChar)
			{
				if (StrQuote == '\0') StrQuote = '\'';
				else if (StrQuote == '\'') StrQuote = '\0';
			}

			else if (Line.substr(i, 2) == "//" && StrQuote == '\0' && !Comments) break;
			else if (Line.substr(i, 2) == "/*" && StrQuote == '\0' && !Comments) Comments = true;
			else if (Line.substr(i, 2) == "*/" && StrQuote == '\0' && Comments) Comments = false;
			if (!Comments) UnCommentedStr += Line[i];

			if (Line[i] == '\\' && StrQuote != '\0') EscapeChar = true;
			else if (EscapeChar) EscapeChar = false;
		}

		if (Startswith(UnCommentedStr, "*/")) UnCommentedStr = ReplaceFirst(UnCommentedStr, "*/");
		return Trim(UnCommentedStr);
	}

	// Check for any irregularities in line.
	static void BracketsNQuotes(const string& Line)
	{
		string NonStringData = InString::ExcludeDataInString(Line);

		// Double and Single quotes
		const int SQUOTE = StrCount(NonStringData, "'");
		const int DQUOTE = StrCount(NonStringData, "\"");

		// Parenthesis
		const int LPAREN = StrCount(NonStringData, "(");
		const int RPAREN = StrCount(NonStringData, ")");

		// Square brackets
		const int LSQUARE = StrCount(NonStringData, "[");
		const int RSQUARE = StrCount(NonStringData, "]");

		if (LPAREN != 0 || RPAREN != 0)
		{
			if (LPAREN > RPAREN) Error::Syntax("'(' was never closed");
			else if (LPAREN < RPAREN) Error::Syntax("Unmatched ')'");
		}

		if (LSQUARE != 0 || RSQUARE != 0)
		{
			if (LSQUARE > RSQUARE) Error::Syntax("'[' was never closed");
			else if (LSQUARE < RSQUARE) Error::Syntax("Unmatched ']'");
		}

		if ((SQUOTE != 0 && !IsEven(SQUOTE)) || (DQUOTE != 0 && !IsEven(DQUOTE)))
			Error::Syntax("Unterminated string literal");
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
			// TODO: Later make the ';' to act as a separator to make single line code a multiline one.
			if (Endswith(Line, ";")) Line = Trim(ReplaceLast(Line, ";")); // Remove ';' from the line.
			Manager::BracketsNQuotes(Line); // Check for incorrect quotes and brackets.

			// TODO: Improve the Lexer.
			vector<string> Tokens = Lexer(Line);
			for (const string& i : Tokens) cout << "[" << i << "]\n";

			// // PERFORM SOME LEXICAL ANALYSIS.
			// vector<string> Tokens = Lexer(Line);
			// if (!Startswith(Tokens[0], "FUN:") && !Startswith(Tokens[0], "ARR:") && Tokens[1].empty()) swap(Tokens[0], Tokens[1]);

			// Tokens[1] = Collections::DataTypes(Tokens[1]); // Classify all datatypes.
			// if (!Startswith(Tokens[1], "FUN:") && !Startswith(Tokens[1], "ARR:") && Tokens[0].empty()) swap(Tokens[0], Tokens[1]);

			// // PARSE THE TOKENS.
			// Parse(Tokens);
		}
    }

	vector<string> Lexer(const string& Line)
	{
		string Lexeme = "";
		vector<string> Tokens;
		return Tokens;
	}

	// EVALUATE A STRING AS THOUGH IT WERE AN EXPRESSION.
	string Evaluator(const string& Line)
	{
		// TODO: Take the Evaluation algorithm that you created from scratch for Studybyte from GitHub.
		// Here's the commit ID of the code which will help you to create this Evaluation system.
		// https://github.com/Light-Lens/Studybyte/blob/4a230cb2dee18cb0b5a5f1e2c84117222c731633/scripts/js/Color.js
		string Operators = "+-*/()";
		return "undefined";
	}

	// // PERFORM SOME LEXICAL ANALYSIS.
	// vector<string> Lexer(const string& Line)
	// {
	// 	bool String, Char = false;
	// 	vector<string> Tokens;
	// 	Tokens.resize(2);

	// 	// Tokenize the functions, arrays and variables.
	// 	for (int i = 0; i < Line.size(); i++)
	// 	{
	// 		if (Line[i] == '"' && !Char)
	// 		{
	// 			if (String) String = false;
	// 			else if (!String) String = true;
	// 		}

	// 		else if (Line[i] == '\'' && !String)
	// 		{
	// 			if (Char) Char = false;
	// 			else if (!Char) Char = true;
	// 		}

	// 		else if (Line[i] == '=' && !String && !Char)
	// 		{
	// 			Tokens = Tokenize(Line, "=");

	// 			Tokens[0] = "VAR:" + Tokens[0];
	// 			Tokens[1] = Trim(ReplaceFirst(Tokens[1], "=", ""));
	// 			break;
	// 		}

	// 		else if (Line[i] == '(' && !String && !Char)
	// 		{
	// 			Tokens = Tokenize(Line, "(");

	// 			Tokens[0] = "FUN:" + Tokens[0];
	// 			Tokens[1] = ConvertToReadableFormat("(" + Tokens[1], "(", ")");
	// 			break;
	// 		}

	// 		else if (Line[i] == '[' && !String && !Char)
	// 		{
	// 			Tokens = Tokenize(Line, "[");

	// 			Tokens[0] = "ARR:" + Tokens[0];
	// 			Tokens[1] = ConvertToReadableFormat("[" + Tokens[1], "[", "]");
	// 			break;
	// 		}

	// 		else if (i >= Line.size() - 1)
	// 		{
	// 			Tokens = Tokenize(Line, "");
	// 			break;
	// 		}
	// 	}

	// 	// Trim out all the spaces from Token list.
	// 	for (int i = 0; i < Tokens.size(); i++) Tokens[i] = Trim(Tokens[i]);
	// 	return Tokens;
	// }

	// PARSE THE TOKENS.
	void Parse(const vector<string>& FormattedLine)
	{
        // THIS PACKAGE MANAGER WILL KEEP TRACK OF ALL CURRENTLY IN-USE PACKAGES.
		if (FormattedLine[0] == "import" && Packages.count(FormattedLine[1]) > 0) Packages[FormattedLine[1]] = true;

		// THESE IF STATEMENTS WILL BE USED FOR VARIABLES DECLARATION AND USAGE.
		else if (FormattedLine[0] == "FUN:Type") GetVarType(FormattedLine[1]);
		else if (Startswith(FormattedLine[0], "VAR:")) DeclareVar(FormattedLine);

		// Data types
		else if (FormattedLine[0] == "None" && FormattedLine[1].empty());
		else if (Startswith(FormattedLine[0], "ARR:") && FormattedLine[1].empty());
		else if (Startswith(FormattedLine[0], "STR:") && FormattedLine[1].empty());
		else if (Startswith(FormattedLine[0], "INT:") && FormattedLine[1].empty());
		else if (Startswith(FormattedLine[0], "BOOL:") && FormattedLine[1].empty());
		else if (Startswith(FormattedLine[0], "FLOAT:") && FormattedLine[1].empty());

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
		else Error::Syntax();
	}
};
