#include "modules/Bus.h"
#include "core/ConsoleUI.h"
#include <iostream>

using namespace std;

Bus::Bus(string id, string routeID, int capacity)
    : Vehicle(id, capacity, routeID) {}

double Bus::calculateMaintenance() const {
    // Large heavy vehicle maintenance cost
    return 5000.0 + (getTotalCapacity() * 150.0);
}

void Bus::displayDetails() const {
    ConsoleUI::printLabelValue("Vehicle ID", getVehicleID());
    ConsoleUI::printLabelValue("Type", "Bus (Heavy Transport)");
    ConsoleUI::printLabelValue("Assigned Route", getAssignedRouteID());
    ConsoleUI::printLabelValue("Capacity Status", to_string(getActivePassengers()) + " / " + to_string(getTotalCapacity()) + " seats occupied");
    ConsoleUI::printLabelValue("Monthly Maintenance Cost", "Rs. " + ConsoleUI::formatDouble(calculateMaintenance()));
}

string Bus::toCSV() const {
    return "Bus," + getVehicleID() + "," + getAssignedRouteID() + "," + to_string(getTotalCapacity()) + "," + to_string(getActivePassengers());
}
