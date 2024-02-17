#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include "main.h"

using namespace std;

int init(int argc, char* argv[])
{
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
    // Matrice del futuro DB
    vector<vector<string>> fields;
    // Riga in costruzione per la matrice fields
    vector<string> current_row;

    readLine(buffer, buffer_size, file);
    buildLine(buffer, current_row);

    vector<int> disabled_fields = exclusionCalc(current_row);
    current_row = excludeElements(current_row, disabled_fields);
    fields.push_back(current_row);

    // Leggi il file riga per riga
    while (true){
        // PULISCI IL BUFFER DELLA RIGA
        current_row.clear();
        // LEGGI DA CSV E METTI IN BUFFER
        readLine(buffer, buffer_size, file);
        // BUFFER A SINGOLO ELEMENTO ----> BUFFER CON CAMPI SPLITTATI
        buildLine(buffer, current_row);
        if (feof(file) || std::string(buffer).find_first_not_of(';') == std::string::npos) { // Se la riga è vuota o contiene solo caratteri di terminazione
            break;
        }
        // ESCLUDI GLI ELEMENTI CHE L'UTENTE NON VUOLE
        current_row = excludeElements(current_row, disabled_fields);
        // PUSH NELLA MATRICE DELLA RIGA CORRETTA
        fields.push_back(current_row);
    }

    fclose(file);

    for (int i = 0; i < fields.size(); i++){
        printLine(fields[i]);
    }

    return 0;
}
