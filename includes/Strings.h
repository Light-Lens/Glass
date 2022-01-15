// Language.h will contain the Lexer and Parser for Glass.
#pragma once

// Glass.h has all required includes for Glass.
#include "../includes/Glass.h"

string ReplaceFirst(const string& FullString, const string& From, const string& To);
string ReplaceLast(const string& FullString, const string& From, const string& To);
string ReplaceAll(const string& FullString, const string& From, const string& To);
string Reverse(const string& FullString);
string Trim(const string& FullString);

bool Startswith(const string& FullString, const string& SubString);
bool Endswith(const string& FullString, const string& SubString);
bool Contains(const string& FullString, const string& SubString);
bool IsNumber(const string& Number);
bool IsAlpha(const string& Text);
bool IsEven(const int& Number);

int StrCount(const string& FullString, const string& SubString);
int IndexOf(const string& FullString, const string& SubString);

vector<string> Split(const string& FullString, const string& SubString="", const bool& SplitFirstWord=false);
