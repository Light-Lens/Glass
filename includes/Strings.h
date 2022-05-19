#pragma once
#include "..\includes\Common.h"

// Check if a substring is in a string or not.
//* NOTE: The string is In-Glass string.
class InString
{
    public:
        static std::string DataInString(const std::string& Line);
        static std::string ExcludeDataInString(const std::string& Line);
        static bool IsInString(const std::string& Line, const std::string& Phrase, const bool& ExcludeString=false);
};

// All string functions
class Strings
{
    public:
        static std::string Trim(const std::string& Sentence);
        static bool IsEven(const int& Number);
        static bool Startswith(const std::string& Sentence, const std::string& WhatToFind);
        static bool Endswith(const std::string& Sentence, const std::string& WhatToFind);
        static bool Find(const std::string& Sentence, const std::string& WhatToFind);
};
