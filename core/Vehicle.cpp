#include "core/Vehicle.h"

using namespace std;

Vehicle::Vehicle(string id, int capacity, string routeID)
    : vehicleID(id), totalCapacity(capacity), assignedRouteID(routeID), activePassengers(0) {}

string Vehicle::getVehicleID() const {
    return vehicleID;
}

string Vehicle::getAssignedRouteID() const {
    return assignedRouteID;
}

int Vehicle::getTotalCapacity() const {
    return totalCapacity;
}

int Vehicle::getActivePassengers() const {
    return activePassengers;
}

void Vehicle::setAssignedRouteID(string routeID) {
    // Empty stub
}

bool Vehicle::incrementPassengers() {
    return false; // Empty stub
}

void Vehicle::decrementPassengers() {
    // Empty stub
}
