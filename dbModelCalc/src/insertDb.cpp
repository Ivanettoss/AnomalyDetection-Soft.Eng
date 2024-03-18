#include "main.h"
#include "sstream"

int insertDb(Con2DB db, vector<string> fields, string tableName, string data)
{
    // Perform the insert operation for the data read
    // INSERT INTO log (field1, field2, field3) VALUES ('value1', 'value2', 'value3');
    string query = "INSERT INTO " + tableName + " (";
    for (size_t i = 0; i < fields.size() - 1; i++)
    {
        query += "\"" + fields[i] + "\"" + ", ";
    }
    query += "\"" + fields[fields.size() - 1] + "\"" + ")" + " VALUES (";
    vector<string> dataSplit = split(data);

    // Check for checksum
    if (dataSplit.size() != fields.size())
    {
        return -100;
    }

    for (size_t i = 0; i < dataSplit.size() - 1; i++)
    {
        query += "\'" + dataSplit[i] + "\', ";
    }
    query += "\'" + dataSplit[dataSplit.size() - 1] + "\'" + ");";

    // Execute the SQL command
    db.ExecSQLcmd(stringToChar(query));

    return 0;
}