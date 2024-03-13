#include "main.h"

using namespace std;

std::vector<int> exclusionCalc(std::vector<std::string>& current_row){
    vector<int> vect;

    cout << "Di seguito verranno presentati i campi rilevati, premere S o N da tastiera per decidere se includerli nel DB" << endl;

    for (long unsigned int i = 0; i < current_row.size(); ++i) {
        char choice;
        if (current_row[i] == "\r"){
            continue;
        }
        cout << "Includere il campo " << i << " (" << current_row[i] << ")? [S/N]: ";
        cin >> choice;

        // Converte il carattere inserito in maiuscolo per semplificare il controllo
        choice = toupper(choice);

        // Controlla se l'utente ha inserito "S" o "N"
        while (choice != 'S' && choice != 'N') {
            cout << "Scelta non valida. Inserire solo S o N: ";
            cin >> choice;
            choice = toupper(choice);
        }

        // Aggiunge l'indice al vettore solo se l'utente ha scelto "S"
        if (choice == 'S') {
            vect.push_back(i);
        }
    }

    return vect;
}

vector<string> excludeElements(const vector<string>& current_row, const vector<int>& exclude_indices) {
    vector<string> result;

    for (long unsigned int i = 0; i < current_row.size(); ++i) {
        if (find(exclude_indices.begin(), exclude_indices.end(), i) != exclude_indices.end()) {
            result.push_back(current_row[i]);
        }
    }
    return result;
}