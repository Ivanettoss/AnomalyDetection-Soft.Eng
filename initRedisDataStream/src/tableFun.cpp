#include "main.h"

using namespace std;

int createTable(Con2DB db, string name, vector<string> fields)
{
    string built = "";
    for (long unsigned int i = 0; i < fields.size() - 1; i++)
    {
        if (fields[i] == "\r" || fields[i] == "\n")
        {
            continue;
        }
        built += "\"" + fields[i] + "\"" + " varchar(" + VARCHARDIM + ")" + ", ";
    }
    if (!(fields[fields.size() - 1] == "\r" || fields[fields.size() - 1] == "\n"))
    {
        built += "\"" + fields[fields.size() - 1] + "\"" + " varchar(" + VARCHARDIM + ")";
    }
    else{
        built = built.substr(0, built.length() - 2);
    }
    if (checkTable(db, name))
    {
        dropTable(db, name);
    }
    string query = "create table " + name + " (measureId serial primary key, " + built + ");";
    db.ExecSQLcmd(stringToChar(query));
    return 0;
}

int checkTable(Con2DB db, string name)
{
    string query = "SELECT EXISTS (SELECT 1 FROM information_schema.tables WHERE table_name = '" + name + "');";
    // Questa query quando viene eseguita ritorna f per false (non trovata), oppure t per true
    PGresult *result = db.ExecSQLtuples(stringToChar(query));
    const char *value = PQgetvalue(result, 0, 0);
    bool r = false;
    if (strcmp(value, "t") == 0)
    {
        r = true;
    }
    else
    {
        r = false;
    }
    return r;
}

void dropTable(Con2DB db, string name)
{
    string query = "drop table \"" + name + "\";";
    db.ExecSQLcmd(stringToChar(query));
}