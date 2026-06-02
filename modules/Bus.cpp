#include "modules/Bus.h"
#include <iostream>

using namespace std;

Bus::Bus(string id, string routeID, int capacity)
    : Vehicle(id, capacity, routeID) {}

double Bus::calculateMaintenance() const {
    return 0.0; // Empty stub
}

void Bus::displayDetails() const {
    // Empty stub
}

string Bus::toCSV() const {
    return ""; // Empty stub
}
