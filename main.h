#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <string>
#include <cstdio>

void readLine(char* buffer, int buffer_size, FILE* file);
void buildLine(char* buffer, std::vector<std::string>& fields);
void printLine(std::vector<std::string> fields);
int findDomain(std::vector<std::string>& fields, std::string comp);

#endif
