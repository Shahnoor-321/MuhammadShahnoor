#pragma once
#include <string>

using namespace std;

struct Item
{
    string name;
    string desc;
    string loc;

    Item() {}

    Item(string n, string d, string l)
        : name(n), desc(d), loc(l) {}
};