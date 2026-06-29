#include "LostFoundSystem.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Easy UI tools
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    cout << "\nPress Enter to return to menu...";
    cin.ignore(10000, '\n');
    cin.get();
}

LostFoundSystem::LostFoundSystem() { 
    loadData(); 
}

int LostFoundSystem::generateNextId() {
    int maxId = 0;
    for (size_t i = 0; i < lostItems.size(); i++) {
        if (lostItems[i].getEntityId() > maxId) maxId = lostItems[i].getEntityId();
    }
    for (size_t i = 0; i < foundItems.size(); i++) {
        if (foundItems[i].getEntityId() > maxId) maxId = foundItems[i].getEntityId();
    }
    return maxId + 1;
}

// Basic empty check input loop
string LostFoundSystem::getInput(string prompt) {
    string value;
    while(true) {
        cout << prompt;
        getline(cin, value);
        if(!value.empty()) return value;
        cout << " [!] Cannot be blank. Please try again.\n";
    }
}

// Writes items to text files using '|' as a simple separator
void LostFoundSystem::saveData() {
    ofstream lOut(lostFile);
    for (size_t i = 0; i < lostItems.size(); i++) {
        lOut << lostItems[i].getEntityId() << "|" << lostItems[i].getItemName() << "|"
             << lostItems[i].getItemDescription() << "|" << lostItems[i].getDate() << "|"
             << lostItems[i].getLocation() << "|" << lostItems[i].getOwnerName() << "|"
             << lostItems[i].getContactNumber() << "|" << lostItems[i].getStatus() << "\n";
    }
    lOut.close();

    ofstream fOut(foundFile);
    for (size_t i = 0; i < foundItems.size(); i++) {
        fOut << foundItems[i].getEntityId() << "|" << foundItems[i].getItemName() << "|"
             << foundItems[i].getItemDescription() << "|" << foundItems[i].getDate() << "|"
             << foundItems[i].getLocation() << "|" << foundItems[i].getFinderName() << "|"
             << foundItems[i].getStorageLocation() << "|" << foundItems[i].getStatus() << "\n";
    }
    fOut.close();
}

// Reads data back from files line by line
void LostFoundSystem::loadData() {
    lostItems.clear(); 
    foundItems.clear();
    
    ifstream lIn(lostFile);
    if (lIn.is_open()) {
        string id, name, desc, date, loc, owner, contact, status;
        while (getline(lIn, id, '|') && getline(lIn, name, '|') &&
               getline(lIn, desc, '|') && getline(lIn, date, '|') &&
               getline(lIn, loc, '|') && getline(lIn, owner, '|') &&
               getline(lIn, contact, '|') && getline(lIn, status)) {
            if(!id.empty()) {
                lostItems.push_back(LostItem(stoi(id), name, desc, date, loc, owner, contact, status));
            }
        }
        lIn.close();
    }

    ifstream fIn(foundFile);
    if (fIn.is_open()) {
        string id, name, desc, date, loc, finder, storage, status;
        while (getline(fIn, id, '|') && getline(fIn, name, '|') &&
               getline(fIn, desc, '|') && getline(fIn, date, '|') &&
               getline(fIn, loc, '|') && getline(fIn, finder, '|') &&
               getline(fIn, storage, '|') && getline(fIn, status)) {
            if(!id.empty()) {
                foundItems.push_back(FoundItem(stoi(id), name, desc, date, loc, finder, storage, status));
            }
        }
        fIn.close();
    }
}

void LostFoundSystem::reportLostItem() {
    clearScreen();
    cout << "========================================\n";
    cout << "         REPORT A LOST ITEM\n";
    cout << "========================================\n";
    cin.ignore(10000, '\n');
    
    string name = getInput(" Enter Item Name            : ");
    string desc = getInput(" Enter Item Description     : ");
    
    string date;
    SimpleDate dummy;
    while(true) {
        cout << " Enter Date (DD/MM/YYYY)    : ";
        getline(cin, date);
        if(dummy.setDateFromString(date)) break;
        cout << " [!] Invalid format. Use DD/MM/YYYY.\n";
    }

    string loc = getInput(" Enter Location Lost        : ");
    string owner = getInput(" Enter Your Name            : ");
    string contact = getInput(" Enter Contact Number       : ");

    int id = generateNextId();
    lostItems.push_back(LostItem(id, name, desc, date, loc, owner, contact));
    saveData();
    
    cout << "\n[+] Successfully saved! Assigned ID: " << id << "\n";
    pauseScreen();
}

void LostFoundSystem::reportFoundItem() {
    clearScreen();
    cout << "========================================\n";
    cout << "         REPORT A FOUND ITEM\n";
    cout << "========================================\n";
    cin.ignore(10000, '\n');

    string name = getInput(" Enter Item Name            : ");
    string desc = getInput(" Enter Item Description     : ");
    
    string date;
    SimpleDate dummy;
    while(true) {
        cout << " Enter Date (DD/MM/YYYY)    : ";
        getline(cin, date);
        if(dummy.setDateFromString(date)) break;
        cout << " [!] Invalid format. Use DD/MM/YYYY.\n";
    }

    string loc = getInput(" Enter Location Found       : ");
    string finder = getInput(" Enter Your Name            : ");
    string storage = getInput(" Enter Current Storage Place: ");

    int id = generateNextId();
    foundItems.push_back(FoundItem(id, name, desc, date, loc, finder, storage));
    saveData();
    
    cout << "\n[+] Successfully saved! Assigned ID: " << id << "\n";
    pauseScreen();
}

// Uses base pointer arrays to show runtime Polymorphism
void LostFoundSystem::displayAllItems() {
    clearScreen();
    cout << "========================================\n";
    cout << "         ALL SYSTEM RECORDS\n";
    cout << "========================================\n";

    if (lostItems.empty() && foundItems.empty()) {
        cout << " No reports registered in the database.\n";
        pauseScreen();
        return;
    }

    SystemEntity* basePtr = nullptr;

    // Print all lost items using polymorphism
    for (size_t i = 0; i < lostItems.size(); i++) {
        basePtr = &lostItems[i];
        basePtr->displayDetails();
    }

    // Print all found items using polymorphism
    for (size_t i = 0; i < foundItems.size(); i++) {
        basePtr = &foundItems[i];
        basePtr->displayDetails();
    }
    pauseScreen();
}

// Matches items automatically by checking if names look identical
void LostFoundSystem::claimAndMatchSystem() {
    clearScreen();
    cout << "========================================\n";
    cout << "       MATCHING AUTO-ENGINE SYSTEM\n";
    cout << "========================================\n";
    bool matchFound = false;

    for (size_t i = 0; i < lostItems.size(); i++) {
        if (lostItems[i].getStatus() == "Resolved") continue;

        for (size_t j = 0; j < foundItems.size(); j++) {
            if (foundItems[j].getStatus() == "Resolved") continue;

            // Get names and dates to compare
            string lostName = lostItems[i].getItemName();
            string foundName = foundItems[j].getItemName();
            string lostDate = lostItems[i].getDate();
            string foundDate = foundItems[j].getDate();

            bool isNameMatch = (lostName == foundName);
            bool isDateMatch = (lostDate == foundDate);
            
            // Check if one name is hidden inside the other name or description
            // (e.g., "HP" is found inside "HP Laptop")
            bool isSimilarText = (foundName.find(lostName) != string::npos || 
                                  lostName.find(foundName) != string::npos ||
                                  lostItems[i].getItemDescription().find(foundName) != string::npos);

            // NEW RULE: Match if names are identical OR (Date matches AND text is similar)
            if (isNameMatch || (isDateMatch && isSimilarText)) {
                matchFound = true;
                cout << "\n[!] POTENTIAL MATCH DETECTED (Date: " << lostDate << "):\n";
                cout << "  * Lost Item : " << lostName << " (Reported by: " << lostItems[i].getOwnerName() << ")\n";
                cout << "  * Found Item: " << foundName << " (Stored at: " << foundItems[j].getStorageLocation() << ")\n";
                cout << " --------------------------------------\n";
                cout << " Mark these cases as Resolved? (y/n): ";
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    lostItems[i].setStatus("Resolved");
                    foundItems[j].setStatus("Resolved");
                    cout << " Case closed successfully.\n";
                }
            }
        }
    }

    if (matchFound) {
        saveData();
    } else {
        cout << " No active matching records found.\n";
    }
    pauseScreen();
}
