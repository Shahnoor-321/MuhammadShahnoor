#ifndef LOSTFOUNDSYSTEM_H
#define LOSTFOUNDSYSTEM_H

#include <vector>
#include <string>
#include "ItemClasses.h"

using namespace std;

class LostFoundSystem {
private:
    vector<LostItem> lostItems;
    vector<FoundItem> foundItems;
    const string lostFile = "lost_items.txt";
    const string foundFile = "found_items.txt";

    int generateNextId();
    string getInput(string prompt);

public:
    LostFoundSystem();
    void saveData();
    void loadData();
    void reportLostItem();
    void reportFoundItem();
    void displayAllItems();
    void claimAndMatchSystem();
};

#endif