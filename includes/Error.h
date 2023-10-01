#pragma once
#include "..\includes\Common.h"

// Generate error messages.
class Error
{
    public:
        static void Syntax(const std::string& details="");
        static void ZeroDivision();
        static void FileFormat(std::string Filename);
        static void OpenFile(std::string Filename);
};
