#include "main.h"

using namespace std;

vector<int> exclusionCalc(vector<string>& current_row){
    vector<int> vect;

    cout << "Below are the detected fields, press S or N on the keyboard to decide whether to include them in the DB" << endl;

    for (size_t i = 0; i < current_row.size(); ++i) {
        char choice;
        if (current_row[i] == "\r"){
            continue;
        }
        cout << "Include field " << i << " (" << current_row[i] << ")? [S/N]: ";
        cin >> choice;

        // Convert the entered character to uppercase for simplification of control
        choice = toupper(choice);

        // Check if the user entered "S" or "N"
        while (choice != 'S' && choice != 'N') {
            cout << "Invalid choice. Please enter only S or N: ";
            cin >> choice;
            choice = toupper(choice);
        }

        // Add the index to the vector only if the user chose "S"
        if (choice == 'S') {
            vect.push_back(i);
        }
    }

    return vect;
}