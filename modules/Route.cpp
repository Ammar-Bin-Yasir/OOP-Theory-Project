#include "modules/Route.h"
#include <sstream>
#include <iostream>

using namespace std;

Route::Route() : distance(0.0) {}

Route::Route(const string& id, const string& start, const string& end, double dist, const string& details)
    : routeID(id), startPoint(start), endPoint(end), distance(dist), routeDetails(details) {}

Route::Route(string csvLine) {
    // Stub
}

string Route::getRouteID() const {
    return routeID;
}

double Route::getDistance() const {
    return distance;
}

string Route::getStartPoint() const {
    return startPoint;
}

string Route::getEndPoint() const {
    return endPoint;
}

string Route::getRouteDetails() const {
    return routeDetails;
}

void Route::displayRoute() const {
    // Stub
}

string Route::toCSV() const {
    return ""; // Stub
}

bool Route::operator==(const Route& other) const {
    return routeID == other.routeID;
}
