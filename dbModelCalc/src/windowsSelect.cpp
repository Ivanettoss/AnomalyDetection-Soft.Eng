#include "main.h"
#include <iostream>
#include <vector>
#include <limits> // Per gestire gli errori di input

using namespace std;

vector<int> windowSelect(int entrynumber)
{
    vector<int> v = {1, 0};
    cout << "There are currently " << entrynumber << " entries detected." << endl;

    do
    {
        cout << "Select a valid initial starting point for the window: " << endl;
        cin >> v[0];

        // Verifica se l'input non è un intero o è negativo
        if (cin.fail() || v[0] < 1) {
            cout << "Invalid input. Please enter a non-negative integer that differs from zero." << endl;
            cin.clear(); // Pulizia dello stato di errore
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora il resto della linea
            v[0] = -1;
        }
    } while (v[0] < 1);

    do
    {
        cout << "Select a valid final point for the window: " << endl;
        cin >> v[1];

        // Verifica se l'input non è un intero o è negativo
        if (cin.fail() || v[1] < 1) {
            cout << "Please enter a valid input." << endl;
            cin.clear(); // Pulizia dello stato di errore
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora il resto della linea
            v[1] = -1;
        }
    } while (v[1] > entrynumber || v[1] < v[0]);

    cout << "Your selected window is: "
         << "Starting point = " << v[0]
         << ", End point = " << v[1] << endl;

    return v;
}
