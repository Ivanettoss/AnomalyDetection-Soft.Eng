#include "main.h"
#include <sstream>


int initCovModel(Con2DB db, vector<string> fields)
{
    // The purpose is to create covariance tables
    // Extract the total number of entries
    stringstream ss;
    string query = "SELECT COUNT(*) FROM log;";
    PGresult *result = (db.ExecSQLtuples(stringToChar(query)));
    int logRows = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    query = "SELECT COUNT(*) FROM average;";
    result = db.ExecSQLtuples(stringToChar(query));
    int avgRows = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    // For each field present in the average table
    for (int i = 1; i <= avgRows; i++)
    {
        // Create the CovField1 table if it does not exist
        if (checkTable(db, "Cov" + fields[i-1]))
        {
            // If it exists, continue
            continue;
        }
        cout << "Unable to find Cov" + fields[i-1] + " model. Creating it..." << endl;
        createTable(db, "\"Cov" + fields[i - 1] + "\"", {"field", "covariance"});
        // For each field present in the average table and different from the currently examined field
        for (int j = 1; j <= avgRows; j++)
        {
            float sum = 0;
            if (i == j)
            {
                continue;
            }
            // Extract the average of the first and second field
            ss << i;
            result = db.ExecSQLtuples(stringToChar("SELECT average FROM average WHERE measureId = '" + ss.str() + "';"));
            float firstAVG = atof(PQgetvalue(result, 0, 0));
            PQclear(result);
            ss.str("");
            ss << j;
            result = db.ExecSQLtuples(stringToChar("SELECT average FROM average WHERE measureId = '" + ss.str() + "';"));
            float secondAVG = atof(PQgetvalue(result, 0, 0));
            PQclear(result);
            ss.str("");
            // For each data in the log
            for (int measure_id = 1; measure_id <= logRows; measure_id++)
            {
                // Build the deviation of the first value from the mean
                ss << measure_id;
                query = "SELECT \"" + fields[i - 1] + "\" FROM log WHERE measureId = '" + ss.str() + "';";
                float dist_1 = atof(PQgetvalue(db.ExecSQLtuples(stringToChar(query)), 0, 0)) - firstAVG;
                // Build the deviation of the second value from the mean
                query = "SELECT \"" + fields[j - 1] + "\" FROM log WHERE measureId = '" + ss.str() + "';";
                ss.str("");
                float dist_2 = atof(PQgetvalue(db.ExecSQLtuples(stringToChar(query)), 0, 0)) - secondAVG;
                // Multiply the two values
                dist_1 *= dist_2;
                // Add to the sum variable
                sum += dist_1;
            }
            // Divide by the total number of entries
            sum /= float(logRows);
            ss << sum;
            // Write the data into the CovField1 table with key Field2 and value sum/measure_id
            insertDb(db, {"field", "covariance"}, "\"Cov" + fields[i - 1] + "\"", fields[j - 1] + " " + ss.str());
            ss.str("");
        }
        cout << "Cov" + fields[i - 1] + " table created" << endl;
    }
    return 0;
}
