// Voglio connettermi alla table "average" del db e stampare il contenuto

#include <ostream>
#include <iostream>
#include <cstring>
#include "con2db/pgsql.h"

#define AVGTABLENAME "average"
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
    PGresult *result;
    string query = "SELECT * FROM ";
    query += AVGTABLENAME;
    query += ";";
    // Ottengo il numero di entry dentro avg, lo uso per poi stampare
    result = db.ExecSQLtuples(stringToChar(query));
    int numRows = PQntuples(result);
    int numFields = PQnfields(result);
    for (int i = 0; i < numRows; i++) {
    // Itera attraverso le colonne
    for (int j = 0; j < numFields; j++) {
        printf("%s\t", PQgetvalue(result, i, j)); // Stampa il valore della cella
    }
    printf("\n");
}
    db.finish();
    return 0;
}