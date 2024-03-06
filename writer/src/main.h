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
#define PSQL_NAME "lollo"
#define PSQL_PASS "lollo"
#define PSQL_PORT "5432"
#define PSQL_DB "AnomalyDetection"
#define PSQL_SERVER "localhost"
#define TOLERANCE 50

using namespace std;

int init(int argc, char* argv[]);

void readLine(char* buffer, int buffer_size, FILE* file);
void buildLine(char* buffer, std::vector<std::string>& fields);
void printLine(std::vector<std::string> fields);
char* stringToChar(std::string str);

int findDomain(std::vector<std::string>& fields, std::string comp);
std::vector<int> exclusionCalc(std::vector<std::string>& current_row);
std::vector<std::string> excludeElements(const std::vector<std::string>& current_row, const std::vector<int>& exclude_indices);
std::vector<std::string> wasteCalc();
std::vector<int> windowSelect(int entry_counter);
float selectTolerance();

Con2DB init_connection(const char* server, const char* port, const char* name, const char* pass, const char* db_name);
int endConnection(Con2DB db);
void init_log(Con2DB db, std::vector<std::string> current_row);

int checkTable(Con2DB db, std::string name);
int createTable(Con2DB db, std::string name, std::vector<std::string> fields);
void dropTable(Con2DB db, std::string name);

std::string getKey(redisReply *reply, int numero);
std::string getValue(redisReply *reply, int numero);

int test(redisContext *context);
#endif
