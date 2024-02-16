#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

int main()
{
    // Nome del file CSV da leggere
    const char *filename = "data1273117654.csv";
    double somma = 0;
    int counter = 0;

    // Apri il file in modalità lettura
    FILE *file = fopen(filename, "r");

    // Verifica se il file è stato aperto correttamente
    if (!file)
    {
        cerr << "Impossibile aprire il file " << filename << endl;
        return 1;
    }

    // Buffer per leggere ogni riga del file
    char buffer[1024];

    // Per ottenere i domini
    fgets(buffer, sizeof(buffer), file);
    buffer[strcspn(buffer, "\n")] = '\0';


    // Leggi il file riga per riga
    while (fgets(buffer, sizeof(buffer), file))
    {
        // Rimuovi il carattere di nuova riga dalla fine della riga letta e sostituiscilo con \0
        // strcspn è una funzione che restituisce la lunghezza della porzione di buffer precedente a \n
        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] > '0'){
            break;
        }

        // Stampa la riga letta
        // cout << "Riga letta: " << buffer << endl;

        // Puoi manipolare la riga come desideri, ad esempio, puoi dividere la riga in campi utilizzando una virgola come delimitatore
        // Esempio: separare la riga in campi utilizzando una virgola come delimitatore e memorizzarli in un vettore
        // Vettore di stringhe chiamato fields che viene reinizializzato ad ogni iterazione del while (non c'è bisogno di fare free perchè std::vector gestisce già tutto)
        vector<string> fields;
        // strok restituisce il puntatore al token trovato prima della virgola, viene usato per dividere la stringa in "campi"
        char *token = strtok(buffer, ",");
        while (token)
        {
            // Pushiamo dentro al vettore fields i token uno per uno, ovvero i valus dei diversi campi per ogni entry
            fields.push_back(token);
            token = strtok(nullptr, ",");
        }

        // Ora hai i campi della riga nel vettore fields, puoi fare ciò che vuoi con essi
        // cout << "Campi della riga: ";
        for (const auto &field : fields)
        {
            cout << field << " ";
        }
        cout << endl;

        // cout << fields[2] << "\n";
        if (fields[2] != " NULL") {
            somma += std::stod(fields[2]);
            counter++;
        }

        /* Stampare la struttura di fields
        cout << "Struttura di fields: ";
        for (const auto &field : fields)
        {
            cout << field << endl;
        }*/

    }

    // Chiudi il file dopo averlo letto e stampando la media
    cout << somma/counter;
    fclose(file);

    return 0;
}
