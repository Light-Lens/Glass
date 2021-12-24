// Language.h will contain the Lexer and Parser for Glass.
#pragma once

// Glass.h has all required includes for Glass.
#include "../includes/Glass.h"

string FormatToRun(const string& Token, const vector<string>& SupportedDataTypes);
string GetVarType(const string& Name);
void DeclareVar(const vector<string>& VarDeclaration);

class Collections
{
//* NOTE: Keep in mind that Functions in this private section must be accessed only by functions of Collections class.
private:
    static void EscapeChars(string& Token, const string& FromEscapeChar, const string& ToEscapeChar)
    {
        // TODO: In a string if there's '\\n' then it should return '\n' (not new line char).
        // TODO: But it's not processing that way, so fix this code.
        if (Contains(Token, FromEscapeChar))
        {
            string NewStr;
            vector<string> NewLine = Split(Token, FromEscapeChar);
            for (int i = 0; i < NewLine.size(); i++)
            {
                if (i >= NewLine.size()-1) NewStr += NewLine[i];
                else NewStr += NewLine[i] + ToEscapeChar;
            }

            Token = NewStr;
        }
    }

/* Classification of DataTypes.
	STR     -> String
	BOOL    -> Boolean
	INT     -> Integer
	FLOAT   -> Floating point
    ARR     -> Array

Parse all the Line and give out some output in accordance to that Line. */
private:
    static string String(const string& Token)
    {
        // TODO: Try to further improve this function.
        if ((Startswith(Token, "\"") && Endswith(Token, "\"")) || (Startswith(Token, "'") && Endswith(Token, "'")))
        {
            string S = Token.substr(1, Token.size()-2);

            // Punctuation characters.
            EscapeChars(S, "\\'", "\'");
            EscapeChars(S, "\\\"", "\"");
            EscapeChars(S, "\\\\", "\\");

            // Control characters.
            EscapeChars(S, "\\n", "\n");
            EscapeChars(S, "\\t", "\t");
            EscapeChars(S, "\\b", "\b");
            EscapeChars(S, "\\r", "\r");
            EscapeChars(S, "\\f", "\f");
            EscapeChars(S, "\\v", "\v");

            return "STR:" + S;
        }

        return "undefined";
    }

    static string Boolean(const string& Token)
    {
        if (Token == "True" || Token == "False") return "BOOL:" + Token;
        return "undefined";
    }

    static string IntFloat(const string& Token)
    {
        if (IsNumber(Token) && (Contains(Token, ".") || Endswith(Token, "f")))
            return "FLOAT:" + ReplaceLast(Token, "f", "");

        else if (IsNumber(Token)) return "INT:" + Token;
        return "undefined";
    }

    static string Array(const string& Token)
    {
        if (Startswith(Token, "[") && Endswith(Token, "]"))
            return "ARR:" + Token.substr(1, Token.size()-2);

        return "undefined";
    }

public:
    static string DataTypes(const string& Token)
    {
        if (Packages.count(Token) > 0) return Token;
        else if (Token.empty() || Token == "None" || Token == "NULL" || Token == "undefined") return "None";
        else if (Token == "True" || Token == "False") return Collections::Boolean(Token);
        else if (IsNumber(Token)) return Collections::IntFloat(Token);
        else if (Contains(Token, "\"") || Contains(Token, "'")) return Collections::String(Token);
        else if (Contains(Token, "[") && Contains(Token, "]")) return Collections::Array(Token);

        return Collections::CheckReference(Token);
    }

	// Check if any variable declaratation rule is violated.
	static bool CheckDeclaration(const string& Name)
	{
        // Use ASCII Table to check the declaration.
        // Check the variable name declaration.
        string VarName = Trim(ReplaceFirst(Name, Name.substr(0, Name.find(":") + 1), ""));
        for (int i = 0; i < VarName.size(); i++)
        {
            if (!((VarName[0] >= 'a' && VarName[0] <= 'z') || (VarName[0] >= 'A' && VarName[0] <= 'Z') || VarName[0] == '_'))
                return false;

            else if (!((VarName[i] >= 'a' && VarName[i] <= 'z') || (VarName[i] >= 'A' && VarName[i] <= 'Z') || (VarName[i] >= '0' && VarName[i] <= '9') || VarName[i] == '_'))
                return false;

            else if (i == VarName.size() - 1) return true;
        }

        return false;
	}

	// Check if any variable is called.
    static string CheckReference(const string& Name)
    {
        string Value = "undefined";
        for (auto const &pair: Variables)
        {
            if (Endswith(pair.first, Name))
                Value = pair.first.substr(0, pair.first.find(":") + 1) + pair.second;
        }

        return Value;
    }
};
