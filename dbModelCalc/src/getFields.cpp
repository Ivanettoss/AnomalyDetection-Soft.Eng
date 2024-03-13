#include "main.h"

vector<string> getFields(Con2DB db, string name)
{
    string query = "SELECT column_name FROM information_schema.columns WHERE table_schema = 'public' AND table_name = '" + name + "';";
    PGresult *result = db.ExecSQLtuples(stringToChar(query));

    int rows = PQntuples(result);
    vector<string> fields;

    // Il ciclo for parte da 1 perchè il primo valore è measureId che è la chiave primaria della log table
    for (int i = 1; i < rows; ++i)
    {
        fields.push_back(PQgetvalue(result, i, 0));
    }
    return fields;
}