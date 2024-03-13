#include "main.h"

int main()
{
    Con2DB db(PSQL_SERVER, PSQL_PORT, PSQL_NAME, PSQL_PASS, PSQL_DB);
    vector<string> waste;
    float tolerance = TOLERANCE;
    // Vedo se la tabella esiste
    if (checkTable(db, "log") == 0)
    {
        cout << "Log table has not been initialized" << endl;
        return -1;
    }
    // Conto le righe nella tabella se esiste
    string query = "SELECT COUNT(*) FROM log";
    PGresult *result = (db.ExecSQLtuples(stringToChar(query)));
    int rows = atoi(PQgetvalue(result, 0, 0));
    if (rows == 0)
    {
        cout << "Log table exists but has no records" << endl;
        return -1;
    }
    PQclear(result);
    // Se arrivo a questo punto del codice devo controllare se esiste un modello (medie e covarianze) già calcolato
    if (DEBUGWASTE)
    {
        // inserisci i valori che vengono considerati di guasto
        waste = wasteCalc();
    }

    if (checkTable(db, "average") == 0)
    {
        cout << "Average table has not been initialized, proceed with creating it..." << endl;
        vector<string> s = {"key", "average"};
        createTable(db, "average", s);
        fillAvgModel(db, waste);
    }
    // Se arrivo qui vuol dire che il modello è presente
    else
    {
        cout << "Average table has been found, would you like to use it?[s]/[n]" << endl;
        cout << "If the choice is NO and log table is found a new model will be created based on the new log" << endl;
        string choice;
        cin >> choice;
        if (!(choice == "s" || choice == "S")){
            // O lo cancello e ne faccio un altro
            dropTable(db, "average");
            vector<string> s = {"key", "average"};
            createTable(db, "average", s);
            fillAvgModel(db, waste);
            cout << "New average model created succesfully!" << endl;
        }
    }

    // Ora per le covarianze
    PQclear(result);
    
    if (checkTable(db, "covariance") == 0)
    {
        cout << "The covariance tables have not been initialized. Proceed with creating them..." << endl;
        
        vector<string> s = {"key", "average"};
        createTable(db, "average", s);
        fillAvgModel(db, waste);
    }
    // Se arrivo qui vuol dire che il modello è presente
    else
    {
        cout << "Average table has been found, would you like to use it?[s]/[n]" << endl;
        cout << "If the choice is NO and log table is found a new model will be created based on the new log" << endl;
        string choice;
        cin >> choice;
        if (!(choice == "s" || choice == "S")){
            // O lo cancello e ne faccio un altro
            dropTable(db, "average");
            vector<string> s = {"key", "average"};
            createTable(db, "average", s);
            fillAvgModel(db, waste);
            cout << "New average model created succesfully!" << endl;
        }
    }



























    // O uso quello presente per trovare le anomalie
    

    // Inserisci il valore per la tolerance della media, lo standard è il 50%
    if (DEBUGTOLERANCE)
    {
        tolerance = selectTolerance();
    }

    if (DEBUGWINDOW)
    {
        vector<int> window = windowSelect(rows - 1);
    }

    return tolerance;
}