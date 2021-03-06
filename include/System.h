#pragma once

#include "Glass.h"

void ConsoleClear();
void ConsoleCMD(const std::string lines);
void ConsoleTitle(const std::string lines);
void ConsoleColor(const std::string lines);
void ConsoleShout(const std::string lines);
void ConsoleShoutln(const std::string lines);
void ConsoleGetKey(const std::string lines);
std::string ConsoleGet(const std::string lines);
std::string SystemArgv(const std::string lines);
std::string SystemEnviron(const std::string lines);
