#pragma once
#include "../includes/Common.h"

// Check if a substring is in a string or not.
//* NOTE: The string is In-Glass string.
class InString
{
    public:
        static string DataInString(const string& Line);
        static string ExcludeDataInString(const string& Line);
        static bool IsInString(const string& Line, const string& Phrase, const bool& ExcludeString=false);
};

// All string functions
class Strings
{
    public:
        static bool Startswith(const string& Sentence, const string& WhatToFind);
        static bool Endswith(const string& Sentence, const string& WhatToFind);
        static bool Find(const string& Sentence, const string& WhatToFind);
};
