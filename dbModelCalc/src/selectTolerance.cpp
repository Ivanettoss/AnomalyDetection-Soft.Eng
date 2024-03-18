#include "main.h"
#include <limits> // To handle input errors

using namespace std;

float selectTolerance()
{
    float tol; // Variable to store tolerance value
    string choice; // Variable to store user choice for changing tolerance

    // Prompt user to change tolerance
    cout << "Standard tolerance is 50%, would you like to change it [s]/[n]: ";
    cin >> choice;

    // Validate user input for choice
    while(choice != "n" && choice != "s"){
        cout << "Please insert a valid answer. [s]/[n]: ";
        cin >> choice;
    }

    // If user chooses not to change tolerance, return default value of 50%
    if(choice == "n") {
        return 50.0f;
    }

    // Input for new tolerance value
    do {
        cout << "Enter the new tolerance value: ";
        cin >> tol;

        // Check if input is not a valid float
        if(cin.fail() || cin.peek() != '\n' || tol < 0) {
            cout << "Invalid input. Please enter a valid value for tolerance." << endl;
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of the line
        } else {
            break; // Exit loop if input is valid
        }
    } while (true);

    return tol; // Return the selected tolerance value
}
