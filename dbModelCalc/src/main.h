#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

#include "con2db/pgsql.h"

#define DEBUGTOLERANCE 0
#define DEBUGWINDOW 0
#define DEBUGWASTE 1
#define TOLERANCE 50

#define VARCHARDIM "50"

#define PSQL_NAME "lollo"
#define PSQL_PASS "lollo"
#define PSQL_PORT "5432"
#define PSQL_DB "AnomalyDetection"
#define PSQL_SERVER "localhost"

using namespace std;

vector<string> wasteCalc();
vector<int> windowSelect(int entry_counter);
float selectTolerance();
char* stringToChar(string str);

int fillAvgModel(Con2DB db, vector<string> waste);

int createTable(Con2DB db, string name, vector<string> fields);
int checkTable(Con2DB db, string name);
void dropTable(Con2DB db, string name);
vector<string> getFields(Con2DB db, string name);
int insertDb(Con2DB db, vector<string> fields, string tableName, string data);