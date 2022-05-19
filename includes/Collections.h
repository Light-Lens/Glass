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
};
