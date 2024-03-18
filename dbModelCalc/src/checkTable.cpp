#include "main.h"

using namespace std;

int checkTable(Con2DB db, string name)
{
    string query = "SELECT EXISTS (SELECT 1 FROM information_schema.tables WHERE table_name = '" + name + "');";
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