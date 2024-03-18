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
        initAvgModel(db, waste);
    }
    // Se arrivo qui vuol dire che il modello è presente
    else
    {
        cout << "The average table has been found, would you like to use it?[s]/[n]" << endl;
        cout << "If the choice is \"n\" a new model will be created based on the new log" << endl;
        string choice;
        cin >> choice;
        if (!(choice == "s" || choice == "S"))
        {
            // O lo cancello e ne faccio un altro
            dropTable(db, "average");
            vector<string> s = {"key", "average"};
            createTable(db, "average", s);
            initAvgModel(db, waste);
            cout << "New average model created succesfully!" << endl;
        }
    }
    covDropAsk(db);

    PQclear(result);

    // Ora per le covarianze, devo controllare che esistano tutte quelle presenti in average, altrimenti le creo
    // Ottengo il nome dei campi presenti in average (sono chiavi)
    vector<string> ins = getKeysCov(db, "average");
    // Per ognuno di questi campi
    for (size_t i = 0; i < ins.size(); i++)
    {
        // Controlla se esiste la tabella chiavamata CovCampo(i)
        if (checkTable(db, "Cov" + ins[i]))
        {
            // Se esiste ok continua
            continue;
        }
        // Se non esiste c'è un problema
        else
        {
            cout << "Unable to find Cov" + ins[i] + " model. Creating it..." << endl;
            createTable(db, "\"Cov" + ins[i] + "\"", {"field", "covariance"});
        }
    }

    cout << "Covariances tables are ready to be used" << endl;

    // Parte del check anomalies
    // Inserisci il valore per la tolerance della media, lo standard è il 50%
    if (DEBUGTOLERANCE)
    {
        tolerance = selectTolerance();
    }

    // La tolleranza è espressa in percentuale, devo scorrere tutti i dati presenti nel log e confrontarli per ogni
    // campo con i valori presenti nella tabella average e nelle tabelle di covarianza

    cout << "Calculating anomalies..." << endl;
    if (checkTable(db, "anomalies") == 1)
    {
        dropTable(db, "anomalies");
    }
    vector<string> s = {"logEntryNumber", "field", "val"};
    createTable(db, "anomalies", s);
    processAnomalies(db, tolerance);
    cout << "New anomalies table created and filled!" << endl;
    cout << "DONE!" << endl;

    return 0;
}