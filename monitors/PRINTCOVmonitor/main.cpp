// Voglio connettermi a tutte le table di covarianza del db e stampare il contenuto

#include <ostream>
#include <iostream>
#include <cstring>
#include "con2db/pgsql.h"

#define PSQL_NAME "lollo"
#define PSQL_PASS "lollo"
#define PSQL_PORT "5432"
#define PSQL_DB "AnomalyDetection"
#define PSQL_SERVER "localhost"

using namespace std;

char* stringToChar(std::string str){
    char* converted = new char[str.length() + 1];
    strcpy(converted, str.c_str());
    return converted;
}

int main(){
    Con2DB db(PSQL_SERVER, PSQL_PORT, PSQL_NAME, PSQL_PASS, PSQL_DB);
    PGresult *resultExt;
    PGresult *resultInt;
    string query = "SELECT tablename FROM pg_tables WHERE schemaname = 'public' AND tablename LIKE 'Cov%';";
    resultExt = db.ExecSQLtuples(stringToChar(query));
    int covQuant = PQntuples(resultExt);
    for (int i = 0; i < covQuant; i++){
        string name = PQgetvalue(resultExt, i, 0);
        // Ognuno di questi è il nome di una tabella di cui voglio stampare il contenuto, richiamo il funz degli altri monitor
        query = "SELECT * FROM ";
        query += "\"" + name + "\"" + ";";
        resultInt = db.ExecSQLtuples(stringToChar(query));
        int numRows = PQntuples(resultInt);
        int numFields = PQnfields(resultInt);
        cout << "----------" + name + " Table ----------" << endl;
        for (int i = 0; i < numRows; i++) {
        // Itera attraverso le colonne
            for (int j = 0; j < numFields; j++) {
                printf("%s\t", PQgetvalue(resultInt, i, j)); // Stampa il valore della cella
            }
            printf("\n");
        }
        PQclear(resultInt);
        printf("\n");
    }
    PQclear(resultExt);
    db.finish();
    return 0;
}