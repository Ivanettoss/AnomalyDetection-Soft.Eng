#include "main.h"

using namespace std;

int createTable(Con2DB db, string name, vector<string> fields)
{
    string built = "";
    for (long unsigned int i = 0; i < fields.size() - 1; i++){
        built += "\"" + fields[i] + "\"" + " varchar(" + VARCHARDIM + ")" + ", ";
    }
    built += "\"" + fields[fields.size() - 1] + "\"" + " varchar(" + VARCHARDIM + ")";
    
    string query = "create table " + name + " (measureId serial primary key, " + built + ");";
    db.ExecSQLcmd(stringToChar(query));
    return 0;
}