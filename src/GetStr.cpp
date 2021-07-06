#include "../include/Glass.h"

using namespace std;

void setConsoleColor(WORD Color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}

bool StrFind(const std::string& MainStr, const std::string& SubString)
{
    if (MainStr.find(SubString) != std::string::npos) return true;
    else return false;
}

bool startswith(const std::string& StartString, const std::string& SubStart)
{
    if (StartString.find(SubStart) == 0) return true;
    else return false;
}

bool endswith(const std::string& EndString, const std::string& SubEnd)
{
    if (EndString.length() >= SubEnd.length())
    {
        return (0 == EndString.compare(EndString.length() - SubEnd.length(), SubEnd.length(), SubEnd));
    }

    else return false;
}

bool getString(const std::string& FullString, const std::string& s1, const std::string& s2)
{
    bool Sw = startswith(FullString, s1);
    bool Ew = endswith(FullString, s2);
    if (Sw == true && Ew == true) return true;
    else return false;
}

std::string replace(const std::string MainString, const std::string& ToRepl, const std::string& WithRepl)
{
    string repl = regex_replace(MainString, regex(ToRepl), WithRepl);
    return repl;
}

std::string join(std::string& JoinString, const std::string& JoinWith)
{
    string Join = JoinString.append(JoinWith);
    return Join;
}

// This function will trim a certain char from the staring and ending of a string.
std::string Trim(const std::string& FullString)
{
    string Whitespace = " \t";
    const auto strBegin = FullString.find_first_not_of(Whitespace);
    if (strBegin == string::npos)
        return "";

    const auto strEnd = FullString.find_last_not_of(Whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return FullString.substr(strBegin, strRange);
}
