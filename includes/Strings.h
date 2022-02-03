// Language.h will contain the Lexer and Parser for Glass.
#pragma once
#include "../includes/Glass.h"

string ReplaceFirst(const string& Source, const string& From, const string& To="");
string ReplaceLast(const string& Source, const string& From, const string& To="");
string ReplaceAll(const string& Source, const string& From, const string& To="");
string Reverse(const string& Source);
string Trim(const string& Source);

bool Startswith(const string& Source, const string& SubString);
bool Endswith(const string& Source, const string& SubString);
bool Contains(const string& Source, const string& SubString);
bool IsNumber(const string& Number);
bool IsAlpha(const string& Text);
bool IsEven(const int& Number);

int StrCount(const string& Source, const string& SubString);
int IndexOf(const string& Source, const string& SubString);

vector<string> Split(const string& Source, const string& SubString="", const bool& SplitFirstWord=false);
