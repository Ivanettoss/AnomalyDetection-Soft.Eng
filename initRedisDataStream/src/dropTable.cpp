#include "main.h"

using namespace std;

void dropTable(Con2DB db, string name)
{
    string query = "drop table \"" + name + "\";";
    db.ExecSQLcmd(stringToChar(query));
}