#include "modules/Route.h"
#include <iostream>

using namespace std;

Route::Route() : routeID(""), startPoint(""), endPoint(""), routeDetails(""), distance(0.0) {}

Route::Route(const string& id, const string& start, const string& end, double dist, const string& details)
    : routeID(id), startPoint(start), endPoint(end), distance(dist), routeDetails(details) {}

Route::Route(string csvLine) {
    // Empty stub
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
    // Empty stub
}

string Route::toCSV() const {
    return ""; // Empty stub
}

double Route::calculateBaseFee(double ratePerKm) const {
    return 0.0; // Empty stub
}

bool Route::operator==(const Route& other) const {
    return false; // Empty stub
}
