#include "SimpleDate.h"
#include <sstream>

using namespace std;

SimpleDate::SimpleDate() {
    day = 1;
    month = 1;
    year = 2026;
}

SimpleDate::SimpleDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

// Splits a string like "25/12/2026" into day, month, and year integers
bool SimpleDate::setDateFromString(string dateStr) {
    stringstream ss(dateStr);
    char slash1, slash2;
    int d, m, y;

    if (ss >> d >> slash1 >> m >> slash2 >> y) {
        if (slash1 == '/' && slash2 == '/' && d >= 1 && d <= 31 && m >= 1 && m <= 12) {
            day = d;
            month = m;
            year = y;
            return true;
        }
    }
    return false;
}

string SimpleDate::getDateString() const {
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}