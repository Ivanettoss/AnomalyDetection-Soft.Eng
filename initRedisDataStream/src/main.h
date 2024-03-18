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

#define DEBUGFIELDSSELECT 1

#define VARCHARDIM "50"
#define PSQL_NAME "lollo"
#define PSQL_PASS "lollo"
#define PSQL_PORT "5432"
#define PSQL_DB "AnomalyDetection"
#define PSQL_SERVER "localhost"

using namespace std;

// Function called by the main program to initialize the Redis stream with CSV file data
int init(int argc, char* argv[]);

// Read a line from the file and put it into buffer
void readLine(char* buffer, int buffer_size, FILE* file);
// Read the buffer and separate the tokens into fields using ";" as delimiter
void buildLine(char* buffer, vector<string>& fields);

// Debug function used to test the correct functioning, now deprecated
// void printLine(vector<string> fields);

// Function that converts a string to char*
char* stringToChar(string str);

// Allows isolating fields that should not be included in calculations
vector<int> exclusionCalc(vector<string>& current_row);
// Excludes from the current string vector those that were not enabled with exclusionCalc
vector<string> excludeElements(const vector<string>& current_row, const vector<int>& exclude_indices);

// Returns 0 if the table with name <name> does not exist in the database, otherwise 1 if it exists
int checkTable(Con2DB db, string name);
// Creates the table <name> within the <db> with fields specified in fields
int createTable(Con2DB db, string name, vector<string> fields);
// Deletes the table <name> from the database
void dropTable(Con2DB db, string name);

#endif
