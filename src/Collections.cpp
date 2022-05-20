#include "..\includes\Common.h"
using namespace std;

// Count the number of times a substring appears in a string.
int Collections::String::Count(const string& Source, const string& SubString)
{
    // https://www.codegrepper.com/code-examples/cpp/find+all+occurrences+of+a+substring+in+a+string+c%2B%2B
    int Count = 0;
    size_t nPos = Source.find(SubString, 0); // First occurrence
    while(nPos != string::npos)
    {
        Count++;
        nPos = Source.find(SubString, nPos+1);
    }

    return Count;
}

// Check whether a string is empty.
bool Collections::String::IsEmpty(const string& Str)
{
    if (Str.empty() || Str.find_first_not_of(" \t\n\v\f\r") == string::npos) return true;
    return false;
}

// Remove empty strings from an array.
vector<string> Collections::Array::Reduce(const vector<string>& arr)
{
    vector<string> new_arr = arr;

    // https://stackoverflow.com/a/60101269/18121288
    auto is_empty = [](const string &s)
    {
        return s.find_first_not_of(" \t\n\v\f\r") == string::npos;
    };

    new_arr.erase(remove_if(begin(new_arr), end(new_arr), is_empty), end(new_arr));
    return new_arr;
}
