// Language.h will contain the Lexer and Parser for Glass.
#pragma once
#include "../includes/Glass.h"

void SystemExit(const int& ExitStatus);
void ConsoleCMD(const string& Command);
void Shout(const string& Message);
void Shoutln(const string& Message);

char GetKey(const string& Key);

string Get(const string& Input);
string SystemEnviron(const string& Environment);
string SystemArgv(const int& Index);
