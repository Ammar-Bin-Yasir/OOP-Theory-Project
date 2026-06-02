#include "modules/Bus.h"
#include <iostream>

using namespace std;

Bus::Bus(string id, string routeID)
    : Vehicle(id, 40, routeID) {}

double Bus::calculateMaintenance() const {
    return 0.0; // Stub
}

void Bus::displayDetails() const {
    // Stub
}

string Bus::toCSV() const {
    return ""; // Stub
}
