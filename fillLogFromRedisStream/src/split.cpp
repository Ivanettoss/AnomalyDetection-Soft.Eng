#include "main.h"
#include "sstream"

vector<string> split(const string &input)
{
    vector<string> risultato;
    istringstream iss(input);
    string token;
    while (getline(iss, token, ' '))
    {
        replace(token.begin(), token.end(), ',', '.');
        risultato.push_back(token);
    }
    return risultato;
}