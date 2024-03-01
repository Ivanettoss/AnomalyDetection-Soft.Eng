#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <algorithm>
#include "con2db/pgsql.h"
#include "con2redis/src/con2redis.h"
#include "con2redis/src/local.h"
#include <hiredis/hiredis.h>

#define BUFFER_SIZE 512
#define DEBUGL 1
#define VARCHARDIM "50"
#define STREAM_NAME "example-stream"

int init(int argc, char* argv[]);

void readLine(char* buffer, int buffer_size, FILE* file);
void buildLine(char* buffer, std::vector<std::string>& fields);
void printLine(std::vector<std::string> fields);
char* stringToChar(std::string str);

int findDomain(std::vector<std::string>& fields, std::string comp);
std::vector<int> exclusionCalc(std::vector<std::string>& current_row);
std::vector<std::string> excludeElements(const std::vector<std::string>& current_row, const std::vector<int>& exclude_indices);

void init_log(std::vector<std::string> current_row);

int createTable(Con2DB db, std::string name, std::vector<std::string> fields);

int test(redisContext *context);
#endif
