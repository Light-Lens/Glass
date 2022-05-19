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
