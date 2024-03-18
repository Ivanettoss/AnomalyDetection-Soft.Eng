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

#define DEBUGWINDOWSELECT 1

#define VARCHARDIM "50"
#define PSQL_NAME "lollo"
#define PSQL_PASS "lollo"
#define PSQL_PORT "5432"
#define PSQL_DB "AnomalyDetection"
#define PSQL_SERVER "localhost"

using namespace std;

// Read a line from the file and put it into a buffer
void readLine(char* buffer, int buffer_size, FILE* file);
// Read the buffer and separate the tokens into fields using ";" as a delimiter
void buildLine(char* buffer, vector<string>& fields);

// Debug function used to test the correct functioning, now deprecated
// void printLine(vector<string> fields);

// Function that converts a string to char*
char* stringToChar(string str);

// New split function that uses space as a separator and returns a vector of strings
vector<string> split(const string &input);
// Allows setting left and right limits (expressed in indices) of the data window to be analyzed
vector<int> windowSelect(int entry_counter);

// Returns 0 if the table with name <name> does not exist in the database, otherwise 1 if it exists
int checkTable(Con2DB db, string name);
// Creates the table <name> within the <db> with fields specified in fields
int createTable(Con2DB db, string name, vector<string> fields);
// Deletes the table <name> from the database
void dropTable(Con2DB db, string name);

// Function that extracts the value from a Redis stream message, currently not used
string getValue(redisReply *reply, int number);
// Function that extracts the key from a Redis stream message, currently not used
string getKey(redisReply *reply, int number);

// Function that initializes the reader from the Redis stream
int reader();
// Given a database db and a table contained within it called "name", returns a vector of strings containing the fields
vector<string> getFields(Con2DB db, string name);
// Given a db, a vector of string fields, the table name, and the data to be inserted separated by space for each field, inserts an entry into the table
int insertDb(Con2DB db, vector<string> fields, string tableName, string data);

#endif
