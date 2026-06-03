#include "modules/Route.h"
#include "core/ConsoleUI.h"
#include <iostream>
#include <sstream>

using namespace std;

Route::Route() : routeID(""), startPoint(""), endPoint(""), stops(""), distance(0.0) {}

Route::Route(const string& id, const string& start, const string& end, double dist, const string& stops)
    : routeID(id), startPoint(start), endPoint(end), distance(dist), stops(stops) {}

Route::Route(string csvLine) {
    stringstream ss(csvLine);
    string distStr;
    getline(ss, routeID, ',');
    getline(ss, startPoint, ',');
    getline(ss, endPoint, ',');
    getline(ss, distStr, ',');
    getline(ss, stops, ',');
    
    // Safety check for empty carriage returns
    if (!stops.empty() && stops.back() == '\r') {
        stops.pop_back();
    }
    
    try {
        distance = stod(distStr);
    } catch (...) {
        distance = 0.0;
    }
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

string Route::getStops() const {
    return stops;
}

void Route::displayRoute() const {
    ConsoleUI::printLabelValue("Route ID", routeID);
    ConsoleUI::printLabelValue("Start Point", startPoint);
    ConsoleUI::printLabelValue("End Point", endPoint);
    ConsoleUI::printLabelValue("Distance", ConsoleUI::formatDouble(distance) + " KM");
    ConsoleUI::printLabelValue("Stops Schedule", stops);
}

string Route::toCSV() const {
    return routeID + "," + startPoint + "," + endPoint + "," + ConsoleUI::formatDouble(distance) + "," + stops;
}

double Route::calculateBaseFee(double ratePerKm) const {
    return distance * ratePerKm;
}

bool Route::operator==(const Route& other) const {
    return this->routeID == other.routeID;
}
