#include "modules/Van.h"
#include <iostream>

using namespace std;

Van::Van(string id, string routeID, int capacity)
    : Vehicle(id, capacity, routeID) {}

double Van::calculateMaintenance() const {
    return 0.0; // Empty stub
}

void Van::displayDetails() const {
    // Empty stub
}

string Van::toCSV() const {
    return ""; // Empty stub
}
