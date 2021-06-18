#pragma once

#include <iostream>
#include <typeinfo>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <random>
#include <regex>
#include <ctime>
#include <map>

#include <windows.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

#include "../include/GetStr.h"
#include "../include/System.h"
#include "../include/Generic.h"
#include "../include/PostThread.h"
#include "../include/Collections.h"

extern std::map<std::string, std::string> variables;
extern std::map<std::string, std::string> VarTypes;

extern int Syspart;
extern int Cgrpart;
extern int Postpart;
extern int FileIOpart;
extern int Webbrowser;
extern int Genericpart;
extern int Collectionpart;

extern int Count;
extern int Comments;

extern std::vector<std::string> Arguments;

void Error(const std::string lines, const std::string num);
