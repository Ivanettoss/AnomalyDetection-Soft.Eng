#include "main.h"

void covDropAsk(Con2DB db)
{
    string choice; // Variable to store user choice

    do
    {
        cout << "Would you like to use existing CovTables? [s]/[n]" << endl;
        cout << "If the choice is \"n\" new covariance tables will be created" << endl;
        cin >> choice;

        if (choice == "s" || choice == "S")
        {
            break; // Exit loop if user chooses to use existing CovTables
        }
        else if (choice == "n" || choice == "N")
        {
            dropAllCov(db); // Drop existing CovTables
            cout << "CovTables dropped successfully" << endl;
            cout << "Creating new covariance model" << endl;
            initCovModel(db, getKeysCov(db, "average")); // Create new covariance model
            break; // Exit loop
        }
        else
        {
            cout << "Invalid choice." << endl;
            continue; // Prompt user again if choice is invalid
        }
    } while (true);
}
