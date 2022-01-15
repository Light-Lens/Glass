// Glass.h has all required includes for Glass.
#include "../includes/Glass.h"

// Only replace the first occurrence.
string ReplaceFirst(const string& FullString, const string& From, const string& To)
{
    string FromStr = From;
    if (From.size() == 1 && !IsAlpha(FromStr)) FromStr = "\\" + From;
    return regex_replace(FullString, regex(FromStr), To, regex_constants::format_first_only);
}

// Only replace the last occurrence.
string ReplaceLast(const string& FullString, const string& From, const string& To)
{
    string FromStr = From;
    if (From.size() == 1 && !IsAlpha(FromStr)) FromStr = "\\" + From;

    string ReversedString = Reverse(FullString);
    string ReplaceLastOccur = regex_replace(ReversedString, regex(FromStr), To, regex_constants::format_first_only);

    return Reverse(ReplaceLastOccur);
}

// Replace all occurrences substring in a string.
string ReplaceAll(const string& FullString, const string& From, const string& To)
{
    string FromStr = From;
    if (From.size() == 1 && !IsAlpha(FromStr)) FromStr = "\\" + From;
	return regex_replace(FullString, regex(FromStr), To);
}

// Reverse the string.
string Reverse(const string& FullString)
{
    string ReverseStr;
    for (int i = FullString.size() - 1; i >= 0; i--) ReverseStr.push_back(FullString[i]);
    return ReverseStr;
}

// Trim a certain char from the staring and ending of a string.
string Trim(const string& FullString)
{
    const string Whitespace = " \t";
    const auto strBegin = FullString.find_first_not_of(Whitespace);
    if (strBegin == string::npos) return "";

    const auto strEnd = FullString.find_last_not_of(Whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return FullString.substr(strBegin, strRange);
}

// Check whether a string startswith a particular substring.
bool Startswith(const string& FullString, const string& SubString)
{
    if (FullString.find(SubString) == 0) return true;
    else return false;
}

// Check whether a string endswith a particular substring.
bool Endswith(const string& FullString, const string& SubString)
{
    if (FullString.length() >= SubString.length())
        return (0 == FullString.compare(FullString.length() - SubString.length(), SubString.length(), SubString));

    else return false;
}

// Check whether a string exists a particular substring.
bool Contains(const string& FullString, const string& SubString)
{
    if (FullString.find(SubString) != string::npos) return true;
    else return false;
}

// Check whether a string is a number (include decimals) or not.
bool IsNumber(const string& Number)
{
    string NewNum = Number;
    if (Number[0] == '-') NewNum = Number.substr(1);
    if (Contains(Number, "_")) NewNum = ReplaceFirst(NewNum, "_", "");
    if (Contains(Number, ".")) NewNum = ReplaceFirst(NewNum, ".", "");
    if (Endswith(Number, "f")) NewNum = NewNum.substr(0, NewNum.size() - 1);
    for (char const &c : NewNum)
    {
        if (isdigit(c) == 0) return false;
    }

    return true;
}

// Check whether a string is an alphabet or not.
bool IsAlpha(const string& Text)
{
    for (int i = 0; i < Text.size(); i++)
    {
        if (!(Text[i] >= 'a' && Text[i] <= 'z') || (Text[i] >= 'A' && Text[i] <= 'Z'))
            return false;
    }

    return true;
}

// Check whether the given number is Odd or Even.
bool IsEven(const int& Number)
{
    return (Number % 2 == 0);
}

// Count the number of times a substring appears in a string.
int StrCount(const string& FullString, const string& SubString)
{
    int StrCount = 0;
    for (int i = 0; i < FullString.size(); i++)
    {
        if (FullString.substr(i, SubString.size()) == SubString)
            StrCount++;
    }

    return StrCount;
}

// Retrive the index of a particular substring.
int IndexOf(const string& FullString, const string& SubString)
{
    return FullString.find(SubString);
}

// Split a string,
// if SplitFirstWord is true split only the first occurrence and leave the rest at it is.
vector<string> Split(const string& FullString, const string& SubString, const bool& SplitFirstWord)
{
    vector<string> SplitArray;

    if (SplitFirstWord == true)
    {
        string SubStr = SubString;
        if (SubString.empty()) SubStr = " ";

        SplitArray.resize(2);
        SplitArray[0] = FullString.substr(0, FullString.find(SubStr));
        SplitArray[1] = FullString.substr(SplitArray[0].size(), FullString.size() - SplitArray[0].size());
        SplitArray[1] = ReplaceFirst(SplitArray[1], SubStr, "");
    }

    else
    {
        if (SubString.empty())
        {
            string SubStr = ReplaceAll(FullString, " ", "");
            SplitArray.resize(SubStr.size());

            // Split the string.
            for (int i = 0; i < SubStr.size(); i++)
                SplitArray[i] = SubStr[i];
        }

        else
        {
            // Code from: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
            int PosStart = 0, PosEnd, DelimLen = SubString.length();
            string Tok;

            while ((PosEnd = FullString.find(SubString, PosStart)) != string::npos)
            {
                Tok = FullString.substr(PosStart, PosEnd - PosStart);
                PosStart = PosEnd + DelimLen;
                SplitArray.push_back(Tok);
            }

            SplitArray.push_back(FullString.substr(PosStart));
        }
    }

	for (int i = 0; i < SplitArray.size(); i++) SplitArray[i] = Trim(SplitArray[i]);
    return SplitArray;
}
