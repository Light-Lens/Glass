#include "../includes/Glass.h"

// Format the token so that it can be used by any C++ function.
string FormatToRun(const string& Token, const vector<string>& SupportedDataTypes)
{
    string GetType = Token.substr(0, Token.find(":"));
    for (int i = 0; i < SupportedDataTypes.size(); i++)
    {
        if (GetType == SupportedDataTypes[i])
            return Token.substr(Token.find(":") + 1, Token.size());

        else if (i >= SupportedDataTypes.size() - 1) Error::Syntax();
    }

    return "undefined";
}

// Get the data type of the variable.
string GetVarType(const string& Name)
{
    string GetType = Name.substr(0, Name.find(":"));
    if (GetType == "STR") return "Type<String>";
    else if (GetType == "INT") return "Type<Integer>";
    else if (GetType == "FLOAT") return "Type<Floating-point>";
    else if (GetType == "BOOL") return "Type<Boolean>";
    else if (GetType == "ARR") return "Type<Array>";
    else if (GetType == "None") return "Type<NULL>";

    return "undefined";
}

// Save the variable into the memory.
void DeclareVar(const vector<string>& VarDeclaration)
{
    string VarValue = "";
    string VarName = Trim(ReplaceFirst(VarDeclaration[0], "VAR:", VarDeclaration[1].substr(0, VarDeclaration[1].find(":") + 1)));
    if (!VarDeclaration[1].empty()) VarValue = VarDeclaration[1].substr(VarDeclaration[1].find(":") + 1, VarDeclaration[1].size());
    if (!Collections::CheckDeclaration(VarName)) Error::Syntax();

    Variables[VarName] = VarValue;
}
