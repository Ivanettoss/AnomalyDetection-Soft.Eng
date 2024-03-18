#include "main.h"
#include <sstream>
#include <map>

int processAnomalies(Con2DB db, float tolerance)
{
    // Count the rows of the log
    float value;
    float upper_bound;
    float lower_bound;
    stringstream ss;
    int rows = atoi(PQgetvalue(db.ExecSQLtuples(stringToChar("SELECT COUNT(*) FROM log;")), 0, 0));
    int avgrows = atoi(PQgetvalue(db.ExecSQLtuples(stringToChar("SELECT COUNT(*) FROM average;")), 0, 0));
    // Save the average values in a map
    map<string, float> dict;
    vector<string> logFields = getFields(db, "log");
    // Load all average values
    PGresult *result = db.ExecSQLtuples(stringToChar("SELECT* FROM average;"));
    for (int i = 0; i < avgrows; i++)
    {
        auto c = find(logFields.begin(), logFields.end(), (PQgetvalue(result, i, 1)));
        if (c != logFields.end())
        {
            dict[PQgetvalue(result, i, 1)] = atof(PQgetvalue(result, i, 2));
        }
    }
    PQclear(result);
    // Loop over the log
    for (int i = 1; i <= rows; i++)
    {
        // For each entry, loop over all fields
        for (auto const &pair : dict)
        {
            // Work only with modeled fields
            ss << i;
            value = atof(PQgetvalue(db.ExecSQLtuples(stringToChar("SELECT \"" + pair.first + "\" FROM log WHERE measureId = '" + ss.str() + "';")), 0, 0));
            ss.str("");
            lower_bound = pair.second - pair.second * tolerance / 100;
            upper_bound = pair.second + pair.second * tolerance / 100;
            if (value >= lower_bound && value <= upper_bound)
            {
                continue;
            }
            // if it's outside
            else
            {
                // insert into the anomalies table where you report the log entry number as KEY and the field as VALUE
                ss << i;
                stringstream val;
                val << value;
                insertDb(db, {"logEntryNumber", "field", "val"}, "anomalies", ss.str() + " " + pair.first + " " + val.str());
                ss.str("");
            }
        }
    }
    return 0;
}
