#pragma once
#include "..\includes\Common.h"

// Manage Arguments, Packages and Comments
class Manager
{
    public:
        static std::vector<std::string> ArgParse(int argc, char const *argv[]);
};

// Change the Color of the Current Line in Console.
class ConsoleColor
{
    public:
        static void SetConsoleColor(WORD Color);
        static void ResetColor();
};
