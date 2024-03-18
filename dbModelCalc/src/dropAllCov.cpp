#include "main.h"

using namespace std;

void dropAllCov(Con2DB db)
{
    string name;
    string query = "SELECT table_name AS table_name FROM information_schema.tables WHERE table_schema = 'public' AND table_name LIKE 'Cov%';";
    PGresult *result = db.ExecSQLtuples(stringToChar(query));
    int row = PQntuples(result);
    for (int i = 0; i < row; i++)
    {
        name = PQgetvalue(result, i, 0);
        if (checkTable(db, name) == 1){
            dropTable(db, name);
        }
    }
}