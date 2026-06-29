#include <iostream>
#include "LostFoundSystem.h"

using namespace std;

int main() {
    LostFoundSystem app;
    int choice;

    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "=============================================\n";
        cout << "      LOST & FOUND MANAGEMENT SYSTEM         \n";
        cout << "=============================================\n";
        cout << "  1. Report a Lost Item\n";
        cout << "  2. Report a Found Item\n";
        cout << "  3. Display All Items\n";
        cout << "  4. Match Lost and Found Items\n";
        cout << "  5. Exit Program\n";
        cout << "=============================================\n";
        cout << " Enter selection (1-5): ";
        
        if (!(cin >> choice)) {
            cout << "\n Invalid selection. Enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Press Enter to try again...";
            cin.get();
            continue;
        }

        switch (choice) {
            case 1: app.reportLostItem(); break;
            case 2: app.reportFoundItem(); break;
            case 3: app.displayAllItems(); break;
            case 4: app.claimAndMatchSystem(); break;
            case 5: 
                cout << "\n Exiting system. Data successfully saved!\n\n";
                break;
            default:
                cout << " Out of bounds selection. Try numbers 1 to 5.\n";
                cin.ignore(10000, '\n');
                cout << "Press Enter to try again...";
                cin.get();
        }
    } while (choice != 5);

    return 0;
}