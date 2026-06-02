#include "modules/Van.h"
#include <iostream>

using namespace std;

Van::Van(string id, string routeID)
    : Vehicle(id, 15, routeID) {}

double Van::calculateMaintenance() const {
    return 0.0; // Stub
}

void Van::displayDetails() const {
    // Stub
}

string Van::toCSV() const {
    return ""; // Stub
}
