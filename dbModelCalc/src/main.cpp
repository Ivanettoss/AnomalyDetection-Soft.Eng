#include "main.h"

int main()
{
    // Establish a connection to the database
    Con2DB db(PSQL_SERVER, PSQL_PORT, PSQL_NAME, PSQL_PASS, PSQL_DB);
    // Vector to hold waste values
    vector<string> waste;
    // Tolerance value for anomaly detection
    float tolerance = TOLERANCE;

    // Check if the "log" table exists
    if (checkTable(db, "log") == 0)
    {
        cout << "Log table has not been initialized" << endl;
        return -1;
    }

    // Count rows in the table if it exists
    string query = "SELECT COUNT(*) FROM log";
    PGresult *result = (db.ExecSQLtuples(stringToChar(query)));
    int rows = atoi(PQgetvalue(result, 0, 0));
    if (rows == 0)
    {
        cout << "Log table exists but has no records" << endl;
        return -1;
    }
    PQclear(result);

    // Check if average and covariance models exist
    if (DEBUGWASTE)
    {
        // Insert values considered as waste
        waste = wasteCalc();
    }

    // Check if the "average" table exists
    if (checkTable(db, "average") == 0)
    {
        cout << "Average table has not been initialized, proceed with creating it..." << endl;
        vector<string> s = {"key", "average"};
        createTable(db, "average", s);
        initAvgModel(db, waste);
    }
    // If the average model exists, prompt the user to use it or create a new one
    else
    {
        cout << "The average table has been found, would you like to use it?[s]/[n]" << endl;
        cout << "If the choice is \"n\" a new model will be created based on the new log" << endl;
        string choice;
        cin >> choice;
        if (!(choice == "s" || choice == "S"))
        {
            // Drop the existing model and create a new one
            dropTable(db, "average");
            vector<string> s = {"key", "average"};
            createTable(db, "average", s);
            initAvgModel(db, waste);
            cout << "New average model created successfully!" << endl;
        }
    }

    // Check and manage covariance models
    covDropAsk(db);

    PQclear(result);

    // Initialize covariance models if missing
    vector<string> ins = getKeysCov(db, "average");
    initCovModel(db, ins);
    cout << "Covariances tables are ready to be used" << endl;

    // Anomaly detection process
    // Set the tolerance value for mean, default is 50%
    if (DEBUGTOLERANCE)
    {
        tolerance = selectTolerance();
    }

    // Compare each data point in the log with the values in the "average" and covariance tables
    cout << "Calculating anomalies..." << endl;
    // Drop the existing "anomalies" table if present
    if (checkTable(db, "anomalies") == 1)
    {
        dropTable(db, "anomalies");
    }
    // Create a new "anomalies" table
    vector<string> s = {"logEntryNumber", "field", "val"};
    createTable(db, "anomalies", s);
    // Process anomalies
    processAnomalies(db, tolerance);
    cout << "New anomalies table created and filled!" << endl;
    cout << "DONE!" << endl;

    return 0;
}
