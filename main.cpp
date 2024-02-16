#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include "main.h"

#define BUFFER_SIZE 512
#define DEBUG 1

using namespace std;

int main(int argc, char* argv[])
{
    // Tutto ciò che segue va spostato in una funzione init() che gestisce anche il passaggio dei parametri

    int buffer_size = BUFFER_SIZE;
    // Aumentare la grandezza del buffer se argc è 3
    if (argc > 2){
        buffer_size *= atoi(argv[2]);
    }

    if (argc > 3){
        cerr << "Too many arguments!" << endl;
        return -1;
    }

    // Nome del file CSV da leggere
    const char *filename = argv[1];

    if (DEBUG > 0) {
        filename = "prova.csv";
    }
    
    // Apri il file in modalità lettura
    FILE *file = fopen(filename, "r");
    
    // Verifica se il file è stato aperto correttamente
    if (!file)
    {
        cerr << " Impossibile aprire il file " << filename << endl;
        return 1;
    }
    
    // Buffer per leggere ogni riga del file e vettore di stringhe per i valori dei campi del DB
    char buffer[buffer_size];
    vector<string> fields;
    // Qui dentro inseriamo gli indici "i" dei campi che si vogliono escludere dai calcoli
    vector<int> disabledFields;

    readLine(buffer, buffer_size, file);
    buildLine(buffer, fields);
    cout << "I campi trovati sono:" << endl;
    printLine(fields);

    // A questo punto del codice devo implementare i controlli sugli input e devo gestire l'evento
    // per il quale l'utente decide quali campi escludere dai calcoli finali


    // Leggi il file riga per riga
    while (true){
        fields.clear();
        readLine(buffer, buffer_size, file);
        buildLine(buffer, fields);
        if (feof(file) || std::string(buffer).find_first_not_of(';') == std::string::npos) { // Se la riga è vuota o contiene solo caratteri di terminazione
            break;
        }
        printLine(fields);
    }

    fclose(file);

    return 0;
}
