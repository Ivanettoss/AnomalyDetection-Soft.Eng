#include "main.h"
#include <limits> // Per gestire gli errori di input

using namespace std;

float selectTolerance()
{
    float tol;
    string choice;
    
    cout << "Standard tolerance is 50%, would you like to change it [s]/[n]: ";
    cin >> choice;
    
    while(choice != "n" && choice != "s"){
        cout << "Please insert a valid answer. [s]/[n]: ";
        cin >> choice;
    }

    // Se l'utente non desidera cambiare la tolleranza, restituisci il valore predefinito del 50%
    if(choice == "n") {
        return 50.0f;
    }

    // Input per la nuova tolleranza
    do {
        cout << "Enter the new tolerance value: ";
        cin >> tol;

        // Verifica se l'input non è un float valido
        if(cin.fail() || cin.peek() != '\n' || tol < 0) {
            cout << "Invalid input. Please enter a valid value for tolerance." << endl;
            cin.clear(); // Pulizia dello stato di errore
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora il resto della linea
        } else {
            break; // Esci dal ciclo se l'input è valido
        }
    } while (true);

    return tol;
}
