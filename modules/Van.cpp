#include "modules/Van.h"
#include "core/ConsoleUI.h"
#include <iostream>

using namespace std;

Van::Van(string id, string routeID, int capacity)
    : Vehicle(id, capacity, routeID) {}

double Van::calculateMaintenance() const {
    // Light vehicle maintenance cost
    return 2500.0 + (getTotalCapacity() * 80.0);
}

void Van::displayDetails() const {
    ConsoleUI::printLabelValue("Vehicle ID", getVehicleID());
    ConsoleUI::printLabelValue("Type", "Van (Light Transport)");
    ConsoleUI::printLabelValue("Assigned Route", getAssignedRouteID());
    ConsoleUI::printLabelValue("Capacity Status", to_string(getActivePassengers()) + " / " + to_string(getTotalCapacity()) + " seats occupied");
    ConsoleUI::printLabelValue("Monthly Maintenance Cost", "Rs. " + ConsoleUI::formatDouble(calculateMaintenance()));
}

string Van::toCSV() const {
    return "Van," + getVehicleID() + "," + getAssignedRouteID() + "," + to_string(getTotalCapacity()) + "," + to_string(getActivePassengers());
}
