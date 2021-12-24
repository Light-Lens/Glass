// Glass.h has all required includes for Glass.
#include "../includes/Glass.h"

void SystemExit(const int& ExitStatus)
{
	exit(ExitStatus);
}

void ConsoleCMD(const string& Command)
{
	system(Command.c_str());
}

void Shout(const string& Message)
{
	cout << Message;
}

void Shoutln(const string& Message)
{
	cout << Message << endl;
}

char GetKey(const string& Key)
{
	cout << Key;
	return getch();
}

string Get(const string& Input)
{
	cout << Input;

	string Given_input = Input; // IF THERE'S A BETTER WAY, CHANGE THIS IN FUTURE!
	getline(cin, Given_input); // Taking input from the user.
	return Given_input;
}

string SystemEnviron(const string& Environment)
{
	int EnvironmentSize = Environment.length();
	char GetEnvironment[EnvironmentSize + 1]; // This will create an empty character array, size of Environment size variable.

	strcpy(GetEnvironment, Environment.c_str()); // Converting String to Const Char*
	return getenv(GetEnvironment); // Returning the value from Environment variable.
}

string SystemArgv(const int& Index)
{
	return Arguments[Index];
}
