#ifndef SIMPLEDATE_H
#define SIMPLEDATE_H

#include <string>

using namespace std;

class SimpleDate {
private:
    int day;
    int month;
    int year;

public:
    SimpleDate();
    SimpleDate(int d, int m, int y);

    bool setDateFromString(string dateStr);
    string getDateString() const;
};

#endif