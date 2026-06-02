#include "modules/TransportPass.h"
#include <sstream>
#include <iostream>

using namespace std;

TransportPass::TransportPass() {}

TransportPass::TransportPass(string pID, string sUname, string rID, string vID, double baseFee, string due)
    : passID(pID), studentUsername(sUname), routeID(rID), vehicleID(vID), status("Pending"), invoice(baseFee, due) {}

TransportPass::TransportPass(string csvLine) {
    // Stub
}

string TransportPass::getPassID() const {
    return passID;
}

string TransportPass::getStudentUsername() const {
    return studentUsername;
}

string TransportPass::getRouteID() const {
    return routeID;
}

string TransportPass::getVehicleID() const {
    return vehicleID;
}

string TransportPass::getStatus() const {
    return status;
}

Bill& TransportPass::getBill() {
    return invoice;
}

void TransportPass::setStatus(string newStatus) {
    status = newStatus;
}

void TransportPass::assignVehicle(string vID) {
    vehicleID = vID;
}

void TransportPass::displayPassDetails() const {
    // Stub
}

string TransportPass::toCSV() const {
    return ""; // Stub
}
