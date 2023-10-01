#pragma once
#include "..\includes\Common.h"

class Collections
{
    public:
        class String
        {
            public:
                static int Count(const std::string& Source, const std::string& SubString);
                static std::string Reduce(const std::string& Str);
                static bool IsEmpty(const std::string& Str);
                static bool HasSpecialChars(const std::string& Str);
                static bool IsString(const std::string& Str);
        };

        class Array
        {
            public:
                static std::vector<std::string> Reduce(const std::vector<std::string>& arr);
                static std::vector<std::string> Filter(const std::vector<std::string>& arr);
                static std::vector<std::string> TrimStart(const std::vector<std::string>& arr);
                static std::vector<std::string> TrimEnd(const std::vector<std::string>& arr);
                static std::vector<std::string> Trim(const std::vector<std::string>& arr);
        };
};
