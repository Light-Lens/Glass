#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

template<typename T> string toString(T str)
{
    ostringstream oss;
    oss << str;
    return oss.str();
}

bool find(const string& source, const string& substring)
{
    if (source.find(substring) != string::npos) return true;
    else return false;
}

int strCount(const string& source, const string& substring)
{
    int StrCount = 0;
    for (int i = 0; i < source.size(); i++)
    {
        if (source.substr(i, substring.size()) == substring) StrCount++;
    }

    return StrCount;
}

string replaceFirst(const string& source, const string& from, const string& to)
{
    string FString = source; // FString means FullString.
    int StartPos = FString.find(from);
    if(StartPos != string::npos) FString.replace(StartPos, from.length(), to);
    return FString;
}

bool isNumber(const string& num)
{
    string newNum = num;
    if (find(num, "."))
    {
        if (strCount(num, ".") == 1) newNum = replaceFirst(newNum, ".", "");
        else if (strCount(num, ".") > 1) return false;
    }

    for (char const &c : newNum)
    {
        if (isdigit(c) == 0) return false;
    }

    return true;
}

int main(int argc, char const *argv[])
{
    string num;
    string expr = "2*(3+6/2)/4";
    // string expr = "(123+2.0)*30";
    vector<string> toks;

    cout << "> " << expr << endl;
    for (int i = 0; i < expr.size(); i++)
    {
        string str_expr = toString(expr[i]);
        if (isNumber(str_expr))
        {
            num += str_expr;
            if (!isNumber(toString(expr[i+1])) && toString(expr[i+1]) != ".")
            {
                if (isNumber(num)) toks.push_back(num);
                // else cout << num << " is not a number." << endl;
            }
        }

        else
        {
            toks.push_back(str_expr);
            num = "";
        }
    }

    for (int i = 0; i < toks.size(); i++) cout << "[" << toks[i] << "]\n";
    return 0;
}
