#pragma once

// These are all important includes!
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <regex>
#include <ctime>

#include <windows.h>
#include <unistd.h>
#include <string.h>
#include <conio.h>

// This will help us to avoid writing 'std::' multiple times.
using namespace std;

// Global variables.
extern int Count;
extern int Comments;

extern string CurrentLine;
extern vector<string> Arguments;
extern map<string, string> Variables;
extern map<string, bool> Packages;

// These are all custom Headers for Glass
#include "../includes/Strings.h"
#include "../includes/Time.h"
#include "../includes/System.h"
#include "../includes/Collections.h"
#include "../includes/Language.h"
