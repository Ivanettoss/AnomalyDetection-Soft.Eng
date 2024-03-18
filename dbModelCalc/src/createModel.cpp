#include "main.h"
#include <sstream>
#include <map>

bool modifiedFind(string da_cercare, vector<string> vettore)
{
    for (size_t i = 0; i < vettore.size(); i++)
    {
        if (vettore[i] == da_cercare)
        {
            return true;
        }
    }
    return false;
}

int initAvgModel(Con2DB db, vector<string> waste)
{
    // Ottieni tutti i campi
    vector<string> fields = getFields(db, "log");
    // Per ogni campo
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
            // Uso un algoritmo per verificare se la stringa è presente nel vettore
            if (modifiedFind(temp, waste))
            {
                cout << "Warning: Potentially invalid data found: rows ";
                cout << j;
                cout << " for column ";
                cout << fields[i] << endl;
            }
            replace(temp.begin(), temp.end(), ',', '.');
            sum += atof(stringToChar(temp));
            counter += 1;
        }
        // Fai la media e inserisci nel db "average" quel valore
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

int initCovModel(Con2DB db, vector<string> fields)
{
    // Lo scopo è creare delle tabelle di covarianza
    // Estrai numero di entry totali
    stringstream ss;
    string query = "SELECT COUNT(*) FROM log;";
    PGresult *result = (db.ExecSQLtuples(stringToChar(query)));
    int logRows = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    query = "SELECT COUNT(*) FROM average;";
    result = db.ExecSQLtuples(stringToChar(query));
    int avgRows = atoi(PQgetvalue(result, 0, 0));
    PQclear(result);
    // Per ogni campo presente nella tabella media
    for (int i = 1; i <= avgRows; i++)
    {
        // Crea la tabella CovCampo1
        createTable(db, "\"Cov" + fields[i - 1] + "\"", {"field", "covariance"});
        // Per ogni campo presente nella tabella media e diverso dal campo attualmente in esame
        for (int j = 1; j <= avgRows; j++)
        {
            float sum = 0;
            if (i == j)
            {
                continue;
            }
            // Estrai la media del primo campo e del secondo
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
            // Per ogni dato presente nel log
            for (int measure_id = 1; measure_id <= logRows; measure_id++)
            {
                // Costruisci lo scarto del primo valore dalla media
                ss << measure_id;
                query = "SELECT \"" + fields[i - 1] + "\" FROM log WHERE measureId = '" + ss.str() + "';";
                float dist_1 = atof(PQgetvalue(db.ExecSQLtuples(stringToChar(query)), 0, 0)) - firstAVG;
                // Costruisci lo scarto del secondo valore dalla media
                query = "SELECT \"" + fields[j - 1] + "\" FROM log WHERE measureId = '" + ss.str() + "';";
                ss.str("");
                float dist_2 = atof(PQgetvalue(db.ExecSQLtuples(stringToChar(query)), 0, 0)) - secondAVG;
                // Moltiplica i due valori
                dist_1 *= dist_2;
                // Aggiungi alla variabile sum
                sum += dist_1;
            }
            // Dividi per il numero totale di entry
            sum /= float(logRows);
            ss << sum;
            // Scrivi il dato nella table CovCampo1 con chiave Campo2 e valore sum/measure_id
            insertDb(db, {"field", "covariance"}, "\"Cov" + fields[i - 1] + "\"", fields[j - 1] + " " + ss.str());
            ss.str("");
        }
        cout << "Cov" + fields[i - 1] + " table created" << endl;
    }
    return 0;
}

// Ho una anomalia quando i valori che scorro lungo log (che ho modellati in average, escludo quindi quelli non modellati) si discostano dalla media
int processAnomalies(Con2DB db, float tolerance)
{
    // Conta le rows del log
    float value;
    float upper_bound;
    float lower_bound;
    stringstream ss;
    int rows = atoi(PQgetvalue(db.ExecSQLtuples(stringToChar("SELECT COUNT(*) FROM log;")), 0, 0));
    int avgrows = atoi(PQgetvalue(db.ExecSQLtuples(stringToChar("SELECT COUNT(*) FROM average;")), 0, 0));
    // Salvati in una mappa i valori medi
    map<string, float> dict;
    vector<string> logFields = getFields(db, "log");
    // Mi carico tutti i valori delle medie
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
    // Fai un ciclo for dove iteri lungo il log
    for (int i = 1; i <= rows; i++)
    {
        // Per ogni entry fai un for dove scorri tutti i campi
        for (auto const &coppia : dict)
        {
            // Lavoro solo con i campi modellati
            ss << i;
            value = atof(PQgetvalue(db.ExecSQLtuples(stringToChar("SELECT \"" + coppia.first + "\" FROM log WHERE measureId = '" + ss.str() + "';")), 0, 0));
            ss.str("");
            lower_bound = coppia.second - coppia.second * tolerance / 100;
            upper_bound = coppia.second + coppia.second * tolerance / 100;
            if (value >= lower_bound && value <= upper_bound)
            {
                continue;
            }
            // se è all'esterno
            else
            {
                // fai un insert dentro alla table anomalies dove riporti il numero di entry del log come CHIAVE e il campo come VALORE
                ss << i;
                stringstream val;
                val << value;
                insertDb(db, {"logEntryNumber", "field", "val"}, "anomalies", ss.str() + " " + coppia.first + " " + val.str());
                ss.str("");
            }
        }
    }
    return 0;
}