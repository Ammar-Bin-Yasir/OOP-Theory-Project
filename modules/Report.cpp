#include "modules/Report.h"
#include "Engine/TransportManager.h"
#include "core/ConsoleUI.h"
#include "modules/Route.h"
#include "core/Vehicle.h"
#include "modules/TransportPass.h"
#include <iostream>

using namespace std;

void RevenueReport::generate(const TransportManager& manager) const {
    double totalPaid = 0.0;
    double totalOutstanding = 0.0;
    int paidCount = 0;
    int unpaidCount = 0;

    const ClassArray<TransportPass*>& passes = manager.getPassList();
    for (int i = 0; i < passes.getSize(); ++i) {
        TransportPass* p = passes[i];
        if (p->getStatus() == "Approved") {
            Bill& bill = p->getBill();
            if (bill.getIsPaid()) {
                totalPaid += bill.getTotalAmount();
                paidCount++;
            } else {
                totalOutstanding += bill.getTotalAmount();
                unpaidCount++;
            }
        }
    }

    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("FINANCIAL REVENUE REPORT");
    ConsoleUI::printLabelValue("Total Revenue Received", "Rs. " + ConsoleUI::formatDouble(totalPaid));
    ConsoleUI::printLabelValue("Total Revenue Outstanding", "Rs. " + ConsoleUI::formatDouble(totalOutstanding));
    ConsoleUI::printLabelValue("Fully Paid Student Accounts", to_string(paidCount));
    ConsoleUI::printLabelValue("Pending/Unpaid Accounts", to_string(unpaidCount));
    ConsoleUI::printDivider();
}

void RouteUsageReport::generate(const TransportManager& manager) const {
    ConsoleUI::clearScreen();
    ConsoleUI::printHeader("ROUTE VEHICLE USAGE & LOAD FACTOR REPORT");

    ClassArray<string> headers;
    headers.add("Route ID");
    headers.add("Assigned Vehicles");
    headers.add("Total Capacity");
    headers.add("Active Passengers");
    headers.add("Available Seating");

    ClassArray<int> widths;
    widths.add(12);
    widths.add(20);
    widths.add(15);
    widths.add(18);
    widths.add(18);

    ClassArray<ClassArray<string>> rows;

    const ClassArray<Route*>& routes = manager.getRouteList();
    const ClassArray<Vehicle*>& vehicles = manager.getVehicleList();

    for (int r = 0; r < routes.getSize(); ++r) {
        string rID = routes[r]->getRouteID();
        
        int assignedVehiclesCount = 0;
        int totalCap = 0;
        int activePass = 0;

        for (int v = 0; v < vehicles.getSize(); ++v) {
            if (vehicles[v]->getAssignedRouteID() == rID) {
                assignedVehiclesCount++;
                totalCap += vehicles[v]->getTotalCapacity();
                activePass += vehicles[v]->getActivePassengers();
            }
        }

        ClassArray<string> row;
        row.add(rID);
        row.add(to_string(assignedVehiclesCount));
        row.add(to_string(totalCap));
        row.add(to_string(activePass));
        row.add(to_string(totalCap - activePass));
        rows.add(row);
    }

    ConsoleUI::printTable(headers, widths, rows);
}
