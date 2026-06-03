#include "modules/TransportPass.h"
#include "core/ConsoleUI.h"
#include <iostream>
#include <sstream>

using namespace std;

TransportPass::TransportPass() : passID(""), studentUsername(""), routeID(""), vehicleID(""), status("Pending") {}

TransportPass::TransportPass(string pID, string sUname, string rID, string vID, double baseFee, string due)
    : passID(pID), studentUsername(sUname), routeID(rID), vehicleID(vID), status("Pending"), invoice(baseFee, due) {}

TransportPass::TransportPass(string csvLine) {
    stringstream ss(csvLine);
    string feeStr, fineStr, isPaidStr, dueDate;
    
    getline(ss, passID, ',');
    getline(ss, studentUsername, ',');
    getline(ss, routeID, ',');
    getline(ss, vehicleID, ',');
    getline(ss, status, ',');
    
    getline(ss, feeStr, ',');
    getline(ss, fineStr, ',');
    getline(ss, dueDate, ',');
    getline(ss, isPaidStr, ',');
    
    if (!isPaidStr.empty() && isPaidStr.back() == '\r') {
        isPaidStr.pop_back();
    }

    double fee = 0.0, fine = 0.0;
    bool paid = false;
    try { fee = stod(feeStr); } catch(...) {}
    try { fine = stod(fineStr); } catch(...) {}
    paid = (isPaidStr == "1");

    invoice = Bill(fee, fine, dueDate, paid);
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
    ConsoleUI::printLabelValue("Pass Application ID", passID);
    ConsoleUI::printLabelValue("Student Username", studentUsername);
    ConsoleUI::printLabelValue("Assigned Route ID", routeID);
    ConsoleUI::printLabelValue("Assigned Vehicle ID", vehicleID.empty() ? "None (Pending Allocation)" : vehicleID);
    
    string statusStyled = status;
    if (status == "Approved") {
        statusStyled = ConsoleUI::GREEN + status + ConsoleUI::RESET;
    } else if (status == "Pending") {
        statusStyled = ConsoleUI::YELLOW + status + ConsoleUI::RESET;
    } else if (status == "Rejected") {
        statusStyled = ConsoleUI::RED + status + ConsoleUI::RESET;
    }
    ConsoleUI::printLabelValue("Pass Status", statusStyled);
    
    cout << "--- Financial Invoice Details ---" << endl;
    invoice.displayBill();
}

string TransportPass::toCSV() const {
    return passID + "," + studentUsername + "," + routeID + "," + vehicleID + "," + status + "," + 
           ConsoleUI::formatDouble(invoice.getMonthlyFee()) + "," + ConsoleUI::formatDouble(invoice.getLateFine()) + "," + 
           invoice.getDueDate() + "," + (invoice.getIsPaid() ? "1" : "0");
}
