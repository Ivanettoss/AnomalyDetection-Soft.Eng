#include "main.h"

bool modifiedFind(string to_find, vector<string> vector)
{
    for (size_t i = 0; i < vector.size(); i++)
    {
        if (vector[i] == to_find)
        {
            return true;
        }
    }
    return false;
}