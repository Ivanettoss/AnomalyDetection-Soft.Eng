#include "main.h"

using namespace std;

vector<string> wasteCalc()
{
    vector<string> waste; // Vector to store special values indicating faults
    string pogg; // Temporary variable to store user input
    string choice; // Variable to store user choice for continuing or exiting

    do
    {
        cout << "Are there any special values indicating faults? (Enter 'n' to exit): " << endl;
        cin >> pogg;
        choice = pogg;

        if (choice == "n")
        {
            return waste; // Return empty vector if user chooses to exit
        }

        // Check if the element already exists in the waste vector
        if (find(waste.begin(), waste.end(), pogg) != waste.end())
        {
            cout << "This value has already been inserted. Please enter a different value." << endl;
            continue;
        }

        waste.push_back(pogg); // Add the special value to the waste vector

        cout << "Would you like to enter another value? (s/n): ";
        cin >> choice;

        if (choice != "s" && choice != "n")
        {
            cout << "Invalid choice. Please enter 's' to continue or 'n' to exit." << endl;
            continue;
        }
    } while (choice != "n");

    return waste; // Return the vector containing special values indicating faults
}