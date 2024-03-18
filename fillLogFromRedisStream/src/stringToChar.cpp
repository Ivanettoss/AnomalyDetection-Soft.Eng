#include "main.h"

char* stringToChar(std::string str){
    char* converted = new char[str.length() + 1];
    strcpy(converted, str.c_str());
    return converted;
}