#include "main.h"

void printLine(std::vector<std::string> fields)
{
    std::string row = "";
    for (const auto &field : fields)
    {
        row += field + " ";
    }
    std::cout << row << std::endl;
}