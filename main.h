#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <string>
#include <cstdio>

#define BUFFER_SIZE 512
#define DEBUG 1

void readLine(char* buffer, int buffer_size, FILE* file);
void buildLine(char* buffer, std::vector<std::string>& fields);
void printLine(std::vector<std::string> fields);
int findDomain(std::vector<std::string>& fields, std::string comp);
int init(int argc, char* argv[]);
std::vector<int> exclusionCalc(std::vector<std::string>& current_row);
std::vector<std::string> excludeElements(const std::vector<std::string>& current_row, const std::vector<int>& exclude_indices);

#endif
