#include "main.h"
#include <sstream>

int initAvgModel(Con2DB db, vector<string> waste)
{
    // Get all fields
    vector<string> fields = getFields(db, "log");
    // For each field
    PGresult *result;
    stringstream ss;
    int rows;
    float sum = 0;
    float counter = 0;
    int checkSum = 0;
    for (size_t i = 0; i < fields.size(); i++)
    {
        result = db.ExecSQLtuples(stringToChar("SELECT \"" + fields[i] + "\" from log;"));
        rows = PQntuples(result);
        for (int j = 0; j < rows; j++)
        {
            string temp(PQgetvalue(result, j, 0));
            // Use an algorithm to check if the string is present in the vector
            if (modifiedFind(temp, waste))
            {
                cout << "Warning: Potentially invalid data found: rows ";
                cout << j + 1;
                cout << " for column ";
                cout << fields[i] << endl;
            }
            replace(temp.begin(), temp.end(), ',', '.');
            sum += atof(stringToChar(temp));
            counter += 1;
        }
        // Calculate the average and insert into the "average" table
        ss << sum / counter;
        checkSum = insertDb(db, getFields(db, "average"), "average", fields[i] + " " + ss.str());
        if (checkSum == -100)
        {
            cout << "Error: unable to parse values for insertDb function." << endl;
            return -1;
        }
        sum = 0;
        counter = 0;
        ss.str("");
    }
    return 0;
}
