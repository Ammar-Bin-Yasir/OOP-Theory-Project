#include "modules/Admin.h"
#include "Engine/TransportManager.h"
#include "core/ConsoleUI.h"
#include "modules/Route.h"
#include "modules/Bus.h"
#include "modules/Van.h"
#include <iostream>

using namespace std;

Admin::Admin(const string& username, const string& password)
    : User(username, password, "Admin") {}

void Admin::showMenu(TransportManager& manager) {
    ClassArray<string> opts;
    opts.add("Add Route");
    opts.add("Add Vehicle");
    opts.add("Update Vehicle Details (Capacity/Route)");
    opts.add("View All Vehicles");
    opts.add("View All Applications");
    opts.add("Process Pass Applications");
    opts.add("Generate Route Usage Report");
    opts.add("Generate Revenue Report");
    opts.add("Advance Billing Cycle (New Month)");
    opts.add("Set System Date");
    opts.add("Logout");

    while (true) {
        int choice = ConsoleUI::showMenu("ADMINISTRATOR CONTROL PANEL", opts);
        if (choice == 1) {
            string id = ConsoleUI::promptString("Enter Route ID (e.g. R01)");
            string start = ConsoleUI::promptString("Enter Start Point");
            string end = ConsoleUI::promptString("Enter End Point");
            double dist = ConsoleUI::promptDouble("Enter Distance in KM", 0.1);
            string stops = ConsoleUI::promptString("Enter Stops Details (e.g. Stop1 - Stop2 - Stop3)");
            Route r(id, start, end, dist, stops);
            manager.addRoute(r);
            ConsoleUI::pause();
        } else if (choice == 2) {
            string id = ConsoleUI::promptString("Enter Vehicle ID (e.g. V01)");
            string routeID = ConsoleUI::promptString("Enter Route ID to assign");
            int typeChoice = ConsoleUI::promptInt("Select Type:\n  [1] Bus (Capacity 40)\n  [2] Van (Capacity 15)\nSelect Type", 1, 2);
            int cap = (typeChoice == 1) ? 40 : 15;
            Vehicle* v = nullptr;
            if (typeChoice == 1) {
                v = new Bus(id, routeID, cap);
            } else {
                v = new Van(id, routeID, cap);
            }
            manager.addVehicle(v);
            ConsoleUI::pause();
        } else if (choice == 3) {
            string id = ConsoleUI::promptString("Enter Vehicle ID to update");
            int newCap = ConsoleUI::promptInt("Enter New Seating Capacity", 5, 100);
            string newRouteID = ConsoleUI::promptString("Enter New Assigned Route ID");
            manager.updateVehicleDetails(id, newCap, newRouteID);
            ConsoleUI::pause();
        } else if (choice == 4) {
            manager.viewAllVehicles();
            ConsoleUI::pause();
        } else if (choice == 5) {
            manager.viewAllApplications();
            ConsoleUI::pause();
        } else if (choice == 6) {
            string passID = ConsoleUI::promptString("Enter Pass Application ID to process");
            bool approve = ConsoleUI::promptConfirm("Do you want to APPROVE this application?");
            manager.processApplication(passID, approve);
            ConsoleUI::pause();
        } else if (choice == 7) {
            manager.generateRouteUsageReport();
            ConsoleUI::pause();
        } else if (choice == 8) {
            manager.generateRevenueReport();
            ConsoleUI::pause();
        } else if (choice == 9) {
            if (ConsoleUI::promptConfirm("Are you sure you want to roll over to the next month's billing cycle? This applies late fines to unpaid bills and generates new invoices.")) {
                manager.advanceBillingCycle();
            }
            ConsoleUI::pause();
        } else if (choice == 10) {
            string newDate = ConsoleUI::promptString("Enter new simulated date (YYYY-MM-DD)");
            manager.setSystemDate(newDate);
            ConsoleUI::printSuccess("System simulated date set to: " + newDate);
            ConsoleUI::pause();
        } else if (choice == 11) {
            break;
        }
    }
}

string Admin::toCSV() const {
    return "Admin," + getUsername() + "," + getPassword() + ",";
}
