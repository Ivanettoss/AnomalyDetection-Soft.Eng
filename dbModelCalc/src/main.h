#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

#include "con2db/pgsql.h"

#define DEBUGTOLERANCE 1
#define DEBUGWASTE 1
#define TOLERANCE 50

#define VARCHARDIM "50"

#define PSQL_NAME "lollo"
#define PSQL_PASS "lollo"
#define PSQL_PORT "5432"
#define PSQL_DB "AnomalyDetection"
#define PSQL_SERVER "localhost"

using namespace std;

// Function to collect special values indicating faults
vector<string> wasteCalc();

// Ask the user whether to use or drop existing covariance tables in the database
void covDropAsk(Con2DB db);

// Select tolerance and return float value
float selectTolerance();

// Function that converts a string to char*
char* stringToChar(string str);

// Returns a bool whether it found the string to_find in the vector
bool modifiedFind(string to_find, vector<string> vector);

// New split function that uses space as a separator and returns a vector of strings
vector<string> split(const string &input);

// Initialize the average model, print warnings if there are values in the entry also present in the waste vector
int initAvgModel(Con2DB db, vector<string> waste);

// Initialize covariance models that do not exist based on user needs and the average table
int initCovModel(Con2DB db, vector<string> fields);

// Process anomalies based on the tolerance value entered by the user
int processAnomalies(Con2DB db, float tolerance);

// Returns 0 if the table with name <name> does not exist in the database, otherwise 1 if it exists
int checkTable(Con2DB db, string name);

// Creates the table <name> within the <db> with fields specified in fields
int createTable(Con2DB db, string name, vector<string> fields);

// Deletes the table <name> from the database
void dropTable(Con2DB db, string name);

// Drop all covariance tables present in the db
void dropAllCov(Con2DB db);

// Ask if existing covariance models should be used
void covDropAsk(Con2DB db);

// Given a database db and a table contained within it called "name", returns a vector of strings containing the fields
vector<string> getFields(Con2DB db, string name);

// Obtain the fields for covariance models
vector<string> getKeysCov(Con2DB db, string name);

// Given a db, a vector of string fields, the table name, and the data to be inserted separated by space for each field, inserts an entry into the table
int insertDb(Con2DB db, vector<string> fields, string tableName, string data);
