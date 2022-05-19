#pragma once
#include "..\includes\Common.h"

// PERFORM SOME LEXICAL ANALYSIS.
class Lexer
{
    private:
        static std::string TrimmedLine;

    private:
        static bool BracketsNQuotes();
        static void Tokenizer();

    public:
        Lexer();
};
