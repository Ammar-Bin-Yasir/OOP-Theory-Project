#include "modules/Student.h"
#include "modules/TransportPass.h"
#include "Engine/TransportManager.h"
#include "core/ConsoleUI.h"
#include <iostream>

using namespace std;

Student::Student(const string& username, const string& password, const string& rollNumber)
    : User(username, password, "Student"), rollNumber(rollNumber), assignedPass(nullptr) {}

string Student::getRollNumber() const {
    return rollNumber;
}

TransportPass* Student::getAssignedPass() const {
    return assignedPass;
}

void Student::linkPass(TransportPass* pass) {
    assignedPass = pass;
}

void Student::unlinkPass() {
    assignedPass = nullptr;
}

string Student::toCSV() const {
    return "Student," + getUsername() + "," + getPassword() + "," + rollNumber;
}

void Student::showMenu(TransportManager& manager) {
    ClassArray<string> opts;
    opts.add("View Available Routes");
    opts.add("Apply for Transport Pass");
    opts.add("View My Active Pass");
    opts.add("Pay Pass Fee");
    opts.add("Cancel Transport Registration");
    opts.add("Logout");

    while (true) {
        int choice = ConsoleUI::showMenu("STUDENT DASHBOARD - " + getUsername(), opts);
        if (choice == 1) {
            manager.viewAvailableRoutes();
            ConsoleUI::pause();
        } else if (choice == 2) {
            if (getAssignedPass() != nullptr) {
                ConsoleUI::printError("You already have an active pass or pending application.");
            } else {
                string routeID = ConsoleUI::promptString("Enter Route ID to apply");
                manager.submitApplication(getUsername(), routeID);
            }
            ConsoleUI::pause();
        } else if (choice == 3) {
            if (getAssignedPass() == nullptr) {
                ConsoleUI::printInfo("You do not have any active or pending transport passes.");
            } else {
                getAssignedPass()->displayPassDetails();
            }
            ConsoleUI::pause();
        } else if (choice == 4) {
            if (getAssignedPass() == nullptr) {
                ConsoleUI::printError("No transport pass found.");
            } else {
                manager.payPassFee(getAssignedPass()->getPassID());
            }
            ConsoleUI::pause();
        } else if (choice == 5) {
            if (getAssignedPass() == nullptr) {
                ConsoleUI::printError("You do not have an active registration to cancel.");
            } else {
                if (ConsoleUI::promptConfirm("Are you sure you want to cancel your transport registration?")) {
                    manager.cancelRegistration(getUsername());
                }
            }
            ConsoleUI::pause();
        } else if (choice == 6) {
            break;
        }
    }
}
