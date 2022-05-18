#pragma once
#include "../includes/Common.h"

// Generate error messages.
class Error
{
    public:
        static void Syntax(const string& details="");
        static void ZeroDivision();
        static void FileFormat(string Filename);
        static void OpenFile(string Filename);
};
