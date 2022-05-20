#pragma once
#include "..\includes\Common.h"

// Check if a substring is in a string or not.
//* NOTE: The string is In-Glass string.
class InString
{
    public:
        static std::vector<std::string> DataInString(const std::string& Line);
        static std::string ExcludeDataInString(const std::string& Line);
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
        template<typename T> static std::string ToString(T value)
        {
            // Convert anything to string.
            // https://stackoverflow.com/a/18576429/18121288
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }
};
