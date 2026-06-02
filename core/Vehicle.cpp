#include "core/Vehicle.h"

using namespace std;

Vehicle::Vehicle(string id, int capacity, string routeID)
    : vehicleID(id), assignedRouteID(routeID), activePassengers(0), totalCapacity(capacity) {}

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
    // Stub
}

bool Vehicle::incrementPassengers() {
    return false; // Stub
}

void Vehicle::decrementPassengers() {
    // Stub
}
