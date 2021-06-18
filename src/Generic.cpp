// All these includes will be used in Glass
#include "../include/Glass.h"

using namespace std; // This will help us not to write std:: multiple times

// This function will be used to generate a random whole number.
std::string RandomRange(const std::string num)
{
    // Create some variable which will replace all the syntax words.
    string repl = replace(num, "\\Random.range", "");
    string repl2 = replace(repl, "\\;", "");
    string repl3 = replace(repl2, "\\(", "");
    string repl4 = replace(repl3, "\\)", "");
    string repl5;

    // Check whether if space is there in "," or not.
    if (StrFind(repl4, ", ")) repl5 = replace(repl4, ", ", " ");
    else if (StrFind(repl4, ",")) repl5 = replace(repl4, ",", " ");

    // Split the string and create "Comma" and "Comma2" variable.
    auto Comma = repl5.substr(0, repl5.find(' '));
    auto Comma2 = repl5.substr(Comma.size() + 1, Comma.find(' '));

    srand((unsigned)time(NULL)); // Set the Seed of time to NULL (Process with PC time).

    // Convert string to int.
    int min = stoi(Comma);
    int max = stoi(Comma2);

    vector<int> Random_number;
    Random_number.resize((max * max) + (min * min));

    // Generate and store lots of random float numbers into a vector array.
    if (Random_number.size() <= 10) Random_number.resize(static_cast<int>(((max * max) + (min * min)) + 10));
    for (int i = 0; i < Random_number.size(); i++)
    {
        Random_number[i] = ((rand() % max) + min);
    }

    int index = rand() % Random_number.size(); // Generate a random index value for Random_number variable.
    return to_string(Random_number[index]); // Return the random number.
}

// This function will be used to generate a random decimal number.
std::string RandomUniform(const std::string num)
{
    // Create some variable which will replace all the syntax words.
    string repl = replace(num, "\\Random.Uniform", "");
    string repl2 = replace(repl, "\\;", "");
    string repl3 = replace(repl2, "\\(", "");
    string repl4 = replace(repl3, "\\)", "");
    string repl5;

    // Check whether if space is there in "," or not.
    if (StrFind(repl4, ", ")) repl5 = replace(repl4, ", ", " ");
    else if (StrFind(repl4, ",")) repl5 = replace(repl4, ",", " ");

    // Split the string and create "Comma" and "Comma2" variable.
    auto Comma = repl5.substr(0, repl5.find(' '));
    auto Comma2 = repl5.substr(Comma.size() + 1, Comma.find(' '));

    // Convert string to int.
    float min = stof(Comma);
    float max = stof(Comma2);

    // Start generating a random float number.
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(min, max);

    vector<float> Random_number;
    Random_number.resize(static_cast<int>((max * max) + (min * min)));

    // Generate and store lots of random float numbers into a vector array.
    if (Random_number.size() <= 10) Random_number.resize(static_cast<int>(((max * max) + (min * min)) + 10));
    for (int i = 0; i < Random_number.size(); i++)
    {
        Random_number[i] = dis(gen);
    }

    srand((unsigned)time(NULL)); // Set the Seed of time to NULL (Process with PC time).
    int index = rand() % Random_number.size(); // Generate a random index value for Random_number variable.
    return to_string(Random_number[index]); // Return the random float number from the vector array of a random index value generated before.
}
