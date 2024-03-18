#include "main.h"

vector<string> getFields(Con2DB db, string name)
{
    // Query to fetch column names from the specified table
    string query = "SELECT column_name FROM information_schema.columns WHERE table_schema = 'public' AND table_name = '" + name + "';";
    PGresult *result = db.ExecSQLtuples(stringToChar(query));

    int rows = PQntuples(result);
    vector<string> fields;

    // The for loop starts from 1 because the first value is measureId which is the primary key of the log table
    for (int i = 1; i < rows; ++i)
    {
        // Adding column names to the fields vector
        fields.push_back(PQgetvalue(result, i, 0));
    }
    // Returning the vector containing column names
    return fields;
}
