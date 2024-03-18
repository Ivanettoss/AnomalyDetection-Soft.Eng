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
#define TOLERANCE 50

#define DEBUGFILENAME 0
#define DEBUGFIELDSSELECT 1
#define DEBUGWINDOW 1

#define VARCHARDIM "50"
#define PSQL_NAME "lollo"
#define PSQL_PASS "lollo"
#define PSQL_PORT "5432"
#define PSQL_DB "AnomalyDetection"
#define PSQL_SERVER "localhost"

using namespace std;

int init(int argc, char* argv[]);

void readLine(char* buffer, int buffer_size, FILE* file);
void buildLine(char* buffer, vector<string>& fields);
void printLine(vector<string> fields);
char* stringToChar(string str);

int findDomain(vector<string>& fields, string comp);
vector<int> exclusionCalc(vector<string>& current_row);
vector<string> excludeElements(const vector<string>& current_row, const vector<int>& exclude_indices);

Con2DB init_connection(const char* server, const char* port, const char* name, const char* pass, const char* db_name);
int endConnection(Con2DB db);
void init_log(Con2DB db, vector<string> current_row);
vector<int> windowSelect(int entrynumber);

int checkTable(Con2DB db, string name);
int createTable(Con2DB db, string name, vector<string> fields);
void dropTable(Con2DB db, string name);

string getKey(redisReply *reply, int numero);
string getValue(redisReply *reply, int numero);

int test(redisContext *context);

// READER FUNCTIONs
int new_reader();

#endif
