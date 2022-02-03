// Language.h will contain the Lexer and Parser for Glass.
#pragma once
#include "../includes/Glass.h"

string FormatToRun(const string& Token, const vector<string>& SupportedDataTypes);
string GetVarType(const string& Name);
void DeclareVar(const vector<string>& VarDeclaration);

class Collections
{
/*
* DataTypes.
[STR, String], [BOOL, Boolean], [INT, Integer], [FLOAT, Floating point], [ARR, Array]

* Functional Keywords.
[ARR, Array], [VAR, Variable], [FUN, Function], [CLASS, Class]
*/
private:
    static string String(const string& Token)
    {
        if ((Startswith(Token, "\"") && Endswith(Token, "\"")) || (Startswith(Token, "'") && Endswith(Token, "'")))
        {
            //? Why 'S'? Don't ask me. But yes, 'S' stands for String.
            // Sorry I didn't had any idea what I'm doing and I still don't know what I'm doing.
            // It's name may or might not change in the future.
            string S = Token.substr(1, Token.size() - 2);
            string NewStr = "";
            for (int i = 0; i < S.size(); i++)
            {
                if (S.substr(i, 2) == "\\\\")
                {
                    i++;
                    NewStr += "\\";
                }

                // Punctuation characters.
                else if (S.substr(i, 2) == "\\'")
                {
                    i++;
                    NewStr += "\'";
                }

                else if (S.substr(i, 2) == "\\\"")
                {
                    i++;
                    NewStr += "\"";
                }

                // Control characters.
                else if (S.substr(i, 2) == "\\n")
                {
                    i++;
                    NewStr += "\n";
                }

                else if (S.substr(i, 2) == "\\t")
                {
                    i++;
                    NewStr += "\t";
                }

                else if (S.substr(i, 2) == "\\b")
                {
                    i++;
                    NewStr += "\b";
                }

                else if (S.substr(i, 2) == "\\r")
                {
                    i++;
                    NewStr += "\r";
                }

                else if (S.substr(i, 2) == "\\f")
                {
                    i++;
                    NewStr += "\f";
                }

                else if (S.substr(i, 2) == "\\v")
                {
                    i++;
                    NewStr += "\v";
                }

                else NewStr += S[i];
            }

            return "STR:" + NewStr;
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
        if (IsNumber(Token))
        {
            if (Endswith(Token, "f") || Endswith(Token, "F")) return "FLOAT:" + Token.substr(0, Token.size() - 1);
            else if (Contains(Token, ".")) return "FLOAT:" + Token;
            else return "INT:" + Token;
        }

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
        // TODO: Fix ',' bug in variable, especially in strings.
        if (Packages.count(Token) > 0) return Token;
        else if (Token.empty() || Token == "None" || Token == "NULL") return "None";
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
