#include "main.h"
#include <sstream>

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

int fillAvgModel(Con2DB db, vector<string> waste)
{
    // Ottieni tutti i campi
    vector<string> fields = getFields(db, "log");
    // Per ogni campo
    PGresult *result;
    stringstream ss;
    int rows;
    float sum = 0;
    float counter = 0;
    for (size_t i = 0; i < fields.size(); i++)
    {
        result = db.ExecSQLtuples(stringToChar("SELECT \"" + fields[i] + "\" from log;"));
        rows = PQntuples(result);
        for (int j = 0; j < rows; j++)
        {
            string temp(PQgetvalue(result, j, 0));
            // Uso un algoritmo per verificare se la stringa è presente nel vettore
            if (modifiedFind(temp, waste)){
                continue;
            }
            replace(temp.begin(), temp.end(), ',', '.');
            sum += atof(stringToChar(temp));
            counter += 1;
        }
        // Fai la media e inserisci nel db "average" quel valore
        ss << sum / counter;
        insertDb(db, getFields(db, "average"), "average", fields[i] + " " + ss.str());
        sum = 0;
        counter = 0;
        ss.str("");
    }
    return 0;
}