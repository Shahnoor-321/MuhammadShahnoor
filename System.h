#pragma once
#include <vector>
#include <string>
#include "Item.h"

using namespace std;

class System
{
public:
    void addLost(Item item);
    void addFound(Item item);

    void loadLost(const string& file);
    void loadFound(const string& file);

    void saveLost(const string& file);
    void saveFound(const string& file);

    string showAll();
    string search(const string& key);

private:
    vector<Item> lost;
    vector<Item> found;
};