#include "main.h"

using namespace std;

vector<string> wasteCalc()
{
    vector<string> waste;
    string pogg;
    string choice;

    do
    {
        cout << "Sono presenti valori speciali che indicano guasti? (Inserisci 'n' per uscire): ";
        cin >> pogg;
        choice = pogg;
        if (choice == "n") {
            return waste;
        }

        // Controllo se l'elemento esiste già nel vettore waste
        if (find(waste.begin(), waste.end(), pogg) != waste.end()) {
            cout << "Questo valore è già stato inserito. Inserisci un valore diverso." << endl;
            continue;
        }

        waste.push_back(pogg);

        cout << "Vuoi inserire un altro valore? (s/n): ";
        cin >> choice;

        if (choice != "s" && choice != "n") {
            cout << "Scelta non valida. Inserisci 's' per continuare o 'n' per uscire." << endl;
            continue;
        }
    } while (choice != "n");

    return waste;
}
