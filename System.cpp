#include "System.h"
#include <fstream>
#include <sstream>

using namespace std;

// ---------------- ADD ----------------
void System::addLost(Item item)
{
    lost.push_back(item);
}

void System::addFound(Item item)
{
    found.push_back(item);
}

// ---------------- LOAD LOST ----------------
void System::loadLost(const string& file)
{
    ifstream in(file);
    string line;

    while (getline(in, line))
    {
        stringstream ss(line);
        string n, d, l;

        getline(ss, n, '|');
        getline(ss, d, '|');
        getline(ss, l, '|');

        lost.push_back(Item(n, d, l));
    }
}

// ---------------- LOAD FOUND ----------------
void System::loadFound(const string& file)
{
    ifstream in(file);
    string line;

    while (getline(in, line))
    {
        stringstream ss(line);
        string n, d, l;

        getline(ss, n, '|');
        getline(ss, d, '|');
        getline(ss, l, '|');

        found.push_back(Item(n, d, l));
    }
}

// ---------------- SAVE LOST ----------------
void System::saveLost(const string& file)
{
    ofstream out(file);

    for (auto& i : lost)
        out << i.name << "|" << i.desc << "|" << i.loc << "\n";
}

// ---------------- SAVE FOUND ----------------
void System::saveFound(const string& file)
{
    ofstream out(file);

    for (auto& i : found)
        out << i.name << "|" << i.desc << "|" << i.loc << "\n";
}

// ---------------- SHOW ALL ----------------
string System::showAll()
{
    string out = "LOST ITEMS:\n";

    for (auto& i : lost)
        out += i.name + " | " + i.desc + " | " + i.loc + "\n";

    out += "\nFOUND ITEMS:\n";

    for (auto& i : found)
        out += i.name + " | " + i.desc + " | " + i.loc + "\n";

    return out;
}

// ---------------- SEARCH ----------------
string System::search(const string& key)
{
    string out = "SEARCH RESULTS:\n";

    for (auto& i : lost)
    {
        if (i.name.find(key) != string::npos ||
            i.desc.find(key) != string::npos)
        {
            out += "[LOST] " + i.name + " | " + i.desc + " | " + i.loc + "\n";
        }
    }

    for (auto& i : found)
    {
        if (i.name.find(key) != string::npos ||
            i.desc.find(key) != string::npos)
        {
            out += "[FOUND] " + i.name + " | " + i.desc + " | " + i.loc + "\n";
        }
    }

    return out;
}