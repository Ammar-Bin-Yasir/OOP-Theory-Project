#include "Engine/TransportManager.h"
#include "core/User.h"
#include "modules/Student.h"
#include "modules/Admin.h"
#include "core/Vehicle.h"
#include "modules/Bus.h"
#include "modules/Van.h"
#include "modules/Route.h"
#include "modules/TransportPass.h"
#include "storage/FileHandler.h"
#include "modules/Report.h"
#include "core/ConsoleUI.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <sstream>

using namespace std;

// Forward declaration of date utility function
static string getNextMonthDate(const string& dateStr);

TransportManager::TransportManager() : currentSystemDate("2026-06-01") {}


TransportManager::~TransportManager() { 
    for (int i = 0; i < userList.getSize(); ++i) delete userList[i];
    for (int i = 0; i < vehicleList.getSize(); ++i) delete vehicleList[i];
    for (int i = 0; i < routeList.getSize(); ++i) delete routeList[i];
    for (int i = 0; i < passList.getSize(); ++i) delete passList[i];
}

void TransportManager::loadSystemData() {

    FileHandler handler("users.txt", "vehicles.txt", "routes.txt", "passes.txt");
    
    handler.loadAllData(*this);

    // Create default admin account if files are empty
    if (userList.getSize() == 0) {
        registerNewUser("admin", "admin", "Admin", "");
    }
}

void TransportManager::saveSystemData() {
    FileHandler handler("users.txt", "vehicles.txt", "routes.txt", "passes.txt");
    handler.saveAllData(*this);
}

void TransportManager::runMainMenu() {

    loadSystemData();

    ClassArray<string> options;
    options.add("User Login");
    options.add("Student Registration");
    options.add("Exit System");

    while (true) 
    {
        // Shows the menu and ask user for options in the given range (1 to 3)
        int choice = ConsoleUI::showMenu("CAMPUS TRANSPORTATION SYSTEM", options);
        
        if (choice == 1) 
        {
            string uname = ConsoleUI::promptString("Enter Username");
            string pword = ConsoleUI::promptString("Enter Password");
            
            // call verifyLogin to verify and return the user object if credentials are correct, otherwise return nullptr
            User* u = verifyLogin(uname, pword);

            if (u) 
            {
                ConsoleUI::printSuccess("Login successful! Welcome " + uname);
                ConsoleUI::pause();

                // Polymorphic call to showMenu of the logged in user, passing the manager reference for them to perform operations
                u->showMenu(*this);

                // After user logs out from their menu, we save the system data to persist any changes they made during their session
                saveSystemData();
            } 
            else 
            {
                ConsoleUI::printError("Invalid username or password.");
                ConsoleUI::pause();
            }
        } 
        else if (choice == 2) 
        {
            string uname = ConsoleUI::promptString("Enter Your Username");
            string pword = ConsoleUI::promptString("Enter Your Password");
            string roll = ConsoleUI::promptString("Enter Roll Number");

            // registers new user if it does not already exist
            if (registerNewUser(uname, pword, "Student", roll)) 
            {
                ConsoleUI::printSuccess("Registration successful! You can now login.");
                saveSystemData();
            } 
            else 
            {
                ConsoleUI::printError("Registration failed. Username may already exist.");
            }

            ConsoleUI::pause();
        } 
        else if (choice == 3) 
        {
            saveSystemData();
            ConsoleUI::printSuccess("Exiting. Thank you for using Campus Transportation System.");
            break;
        }
    }
}

// Authentication & Registration
User* TransportManager::verifyLogin(const string& username, const string& password) const {
    User* u = findUser(username);

    // if user exists and password is correct
    if (u && u->checkPassword(password)) {
        return u;
    }
    return nullptr;
}

bool TransportManager::registerNewUser(const string& username, const string& password, const string& role, const string& details) {
    if (findUser(username) != nullptr) return false;
    
    if (role == "Admin") 
    {
        userList.add(new Admin(username, password));
        return true;
    } 
    else if (role == "Student") 
    {
        userList.add(new Student(username, password, details));
        return true;
    }
    return false;
}

// Admin Panel Methods
void TransportManager::addVehicle(Vehicle* newVehicle) 
{
    // Basic validation to ensure vehicle is not null and ID is unique
    if (!newVehicle) return;
    if (findVehicle(newVehicle->getVehicleID())) 
    {
        ConsoleUI::printError("Vehicle ID already exists!");
        delete newVehicle;
        return;
    }

    vehicleList.add(newVehicle);
    ConsoleUI::printSuccess("Vehicle added successfully.");
}

void TransportManager::removeVehicle(const string& vehicleID) 
{
    for (int i = 0; i < vehicleList.getSize(); ++i) 
    {
        if (vehicleList[i]->getVehicleID() == vehicleID) 
        {
            delete vehicleList[i];
            vehicleList.remove(i);
            ConsoleUI::printSuccess("Vehicle removed successfully.");
            return;
        }
    }
    ConsoleUI::printError("Vehicle ID not found!");
}

void TransportManager::updateVehicleDetails(const string& vehicleID, int newCapacity, const string& newRouteID) 
{
    Vehicle* v = findVehicle(vehicleID);
    if (!v) {
        ConsoleUI::printError("Vehicle ID not found!");
        return;
    }
    
    if (!newRouteID.empty() && !findRoute(newRouteID)) {
        ConsoleUI::printError("Assigned Route ID does not exist!");
        return;
    }

    v->setAssignedRouteID(newRouteID);
    ConsoleUI::printSuccess("Vehicle assignments updated successfully.");
}

void TransportManager::viewAllVehicles() const 
{
    if (vehicleList.getSize() == 0) {
        ConsoleUI::printInfo("No vehicles registered in the system.");
        return;
    }

    ClassArray<string> headers;
    headers.add("Vehicle ID");
    headers.add("Assigned Route");
    headers.add("Occupancy");
    headers.add("Capacity");
    headers.add("Maint. Cost");

    ClassArray<int> widths;
    widths.add(12);
    widths.add(16);
    widths.add(10);
    widths.add(10);
    widths.add(15);

    ClassArray<ClassArray<string>> rows;

    for (int i = 0; i < vehicleList.getSize(); ++i) 
    {
        Vehicle* v = vehicleList[i];
        ClassArray<string> row;
        row.add(v->getVehicleID());
        row.add(v->getAssignedRouteID().empty() ? "Unassigned" : v->getAssignedRouteID());
        row.add(to_string(v->getActivePassengers()));
        row.add(to_string(v->getTotalCapacity()));
        row.add("Rs. " + ConsoleUI::formatDouble(v->calculateMaintenance()));

        rows.add(row);
    }

    ConsoleUI::printHeader("REGISTERED VEHICLES");
    ConsoleUI::printTable(headers, widths, rows);
}

void TransportManager::addRoute(const Route& newRoute) 
{
    if (findRoute(newRoute.getRouteID())) {
        ConsoleUI::printError("Route ID already exists!");
        return;
    }
    routeList.add(new Route(newRoute));
    ConsoleUI::printSuccess("Route added successfully.");
}

void TransportManager::assignVehicleToRoute(const string& vehicleID, const string& routeID) 
{
    Vehicle* v = findVehicle(vehicleID);
    Route* r = findRoute(routeID);
    if (!v || !r) {
        ConsoleUI::printError("Vehicle or Route ID not found!");
        return;
    }

    v->setAssignedRouteID(routeID);
    ConsoleUI::printSuccess("Vehicle assigned successfully.");
}

void TransportManager::viewAllApplications() const 
{
    if (passList.getSize() == 0) {
        ConsoleUI::printInfo("No transport pass applications found.");
        return;
    }

    ClassArray<string> headers;
    headers.add("Pass ID");
    headers.add("Student");
    headers.add("Route");
    headers.add("Vehicle");
    headers.add("Status");
    headers.add("Monthly Fee");

    ClassArray<int> widths;
    widths.add(10);
    widths.add(15);
    widths.add(10);
    widths.add(12);
    widths.add(12);
    widths.add(15);

    ClassArray<ClassArray<string>> rows;
    for (int i = 0; i < passList.getSize(); ++i) 
    {
        TransportPass* p = passList[i];

        ClassArray<string> row;
        row.add(p->getPassID());
        row.add(p->getStudentUsername());
        row.add(p->getRouteID());
        row.add(p->getVehicleID().empty() ? "Pending" : p->getVehicleID());
        row.add(p->getStatus());
        row.add("Rs. " + ConsoleUI::formatDouble(p->getBill().getMonthlyFee()));

        rows.add(row);
    }

    ConsoleUI::printHeader("TRANSPORT PASS APPLICATIONS");
    ConsoleUI::printTable(headers, widths, rows);
}

void TransportManager::processApplication(const string& passID, bool approve) 
{
    TransportPass* p = findPass(passID);
    if (!p) {
        ConsoleUI::printError("Pass ID not found.");
        return;
    }

    if (p->getStatus() != "Pending") {
        ConsoleUI::printError("This pass has already been processed.");
        return;
    }

    if (!approve) {
        p->setStatus("Rejected");
        ConsoleUI::printSuccess("Application rejected.");
        return;
    }

    // Check if there is an available vehicle with capacity on the requested route
    Vehicle* allocatedVehicle = nullptr;

    for (int i = 0; i < vehicleList.getSize(); ++i) 
    {
        Vehicle* v = vehicleList[i];
        if (v->getAssignedRouteID() == p->getRouteID() && v->getActivePassengers() < v->getTotalCapacity()) 
        {
            allocatedVehicle = v;
            break;
        }
    }

    if (!allocatedVehicle) {
        ConsoleUI::printError("No available seating capacity on vehicles for Route " + p->getRouteID() + ". Cannot approve pass.");
        return;
    }

    // Allocate resource and increment occupancy count
    allocatedVehicle->incrementPassengers();
    p->assignVehicle(allocatedVehicle->getVehicleID());
    p->setStatus("Approved");

    ConsoleUI::printSuccess("Application Approved! Allocated Vehicle: " + allocatedVehicle->getVehicleID());
}

void TransportManager::generateRouteUsageReport() const {
    RouteUsageReport r;
    r.generate(*this);
}

void TransportManager::generateRevenueReport() const {
    RevenueReport r;
    r.generate(*this);
}

string TransportManager::getSystemDate() const {
    return currentSystemDate;
}

void TransportManager::setSystemDate(const string& newDate) {
    currentSystemDate = newDate;
}

void TransportManager::advanceBillingCycle() 
{
    currentSystemDate = getNextMonthDate(currentSystemDate);
    
    // Process billing roll over for each approved pass
    for (int i = 0; i < passList.getSize(); ++i) 
    {
        TransportPass* p = passList[i];

        // Only process passes that are currently approved and active
        if (p->getStatus() == "Approved") 
        {
            Bill& bill = p->getBill();
            if (!bill.getIsPaid()) {
                // Apply Rs. 150 fine if overdue
                bill.applyLateFine(150.0);
                ConsoleUI::printInfo("Overdue account " + p->getPassID() + " fined Rs. 150.");
            } 
            else 
            {
                // Re-invoice for the new month cycle
                bill.setPaidStatus(false);
            }
        }
    }
    ConsoleUI::printSuccess("Billing cycle rolled over! New Simulated System Month Date: " + currentSystemDate);
}

void TransportManager::viewAvailableRoutes() const 
{
    if (routeList.getSize() == 0) {
        ConsoleUI::printInfo("No transport routes registered.");
        return;
    }

    ConsoleUI::printHeader("AVAILABLE ROUTES");

    int cardWidth = 100;

    // make cards for each route with details and stops schedule
    for (int i = 0; i < routeList.getSize(); ++i) 
    {
        Route* r = routeList[i];

        // Top Border of Card
        cout << ConsoleUI::SECONDARY_COLOR << ConsoleUI::BOLD << "┌";
        for (int j = 0; j < cardWidth - 2; ++j) cout << "─";
        cout << "┐" << endl;

        // Line 1: Route ID and Distance
        stringstream distSs;
        distSs << fixed << setprecision(2) << r->getDistance();

        string infoLeft = " Route ID: " + r->getRouteID();
        string infoRight = "Distance: " + distSs.str() + " KM ";

        int fillSpaces = cardWidth - 2 - infoLeft.length() - infoRight.length();
        if (fillSpaces < 0) fillSpaces = 0;
        
        cout << "│" << ConsoleUI::RESET << ConsoleUI::BOLD << ConsoleUI::SECONDARY_COLOR << infoLeft;
        for (int s = 0; s < fillSpaces; ++s) cout << " ";
        cout << infoRight << ConsoleUI::SECONDARY_COLOR << ConsoleUI::BOLD << "│" << endl;

        // Middle Divider
        cout << "├";
        for (int j = 0; j < cardWidth - 2; ++j) cout << "─";
        cout << "┤" << endl;

        // Line 2: Stops header
        string stopsHeader = " Stops Schedule:";
        int shSpaces = cardWidth - 2 - stopsHeader.length();
        cout << "│" << ConsoleUI::RESET << ConsoleUI::SECONDARY_COLOR << stopsHeader;
        for (int s = 0; s < shSpaces; ++s) cout << " ";
        cout << ConsoleUI::SECONDARY_COLOR << ConsoleUI::BOLD << "│" << endl;

        // Wrapped stops list
        ClassArray<string> wrappedLines;

        string stops = r->getStops();
        stringstream ss(stops);

        string currentLine = "";
        string word;
        while (ss >> word) 
        {
            // If current line is empty, we can add a words in it
            if (currentLine.empty()) {
                currentLine = "   " + word;
            } 
            // Check if there is enough space to add a new word without exceeding the limit
            else if (currentLine.length() + 1 + word.length() <= cardWidth - 6) {
                currentLine += " " + word;
            } 
            // If adding the next word exceeds the line limit, wrap to the next line
            else {
                wrappedLines.add(currentLine);
                currentLine = "   " + word;
            }
        }
        if (!currentLine.empty()) {
            wrappedLines.add(currentLine);
        }

        // After the loop, our stops have been formatted correctly and stored in the wrappedLine string array, now we just print them

        for (int l = 0; l < wrappedLines.getSize(); ++l) 
        {
            string lineText = wrappedLines[l];

            int spaces = cardWidth - 2 - lineText.length();
            if (spaces < 0) spaces = 0;

            cout << "│" << ConsoleUI::RESET << ConsoleUI::SECONDARY_COLOR << lineText;
            for (int s = 0; s < spaces; ++s) cout << " ";
            cout << ConsoleUI::SECONDARY_COLOR << ConsoleUI::BOLD << "│" << endl;
        }

        // Bottom Border of Card
        cout << "└";
        for (int j = 0; j < cardWidth - 2; ++j) cout << "─";
        cout << "┘" << ConsoleUI::RESET << endl << endl;
    }
}

void TransportManager::submitApplication(const string& studentUsername, const string& routeID) 
{
    Route* r = findRoute(routeID);
    if (!r) {
        ConsoleUI::printError("Route ID not found!");
        return;
    }

    // generate unique Pass ID
    string pID = "P" + to_string(passList.getSize() + 101);
    
    // Fee calculation based on route distance (base Rs. 80 per KM)
    double calculatedFee = r->calculateBaseFee(150.0);
    
    // Set payment due date to 15th of the current month
    string due = currentSystemDate.substr(0, 8) + "15";

    TransportPass* newPass = new TransportPass(pID, studentUsername, routeID, "", calculatedFee, due);
    passList.add(newPass);

    // Link student
    User* u = findUser(studentUsername);
    if (u && u->getRole() == "Student") {
        Student* s = static_cast<Student*>(u);
        s->linkPass(newPass);
    }

    ConsoleUI::printSuccess("Application submitted successfully! Pass ID: " + pID + " (Pending Admin Approval)");
}

void TransportManager::viewMyApplications(const string& studentUsername) const 
{
    User* u = findUser(studentUsername);
    if (u && u->getRole() == "Student") 
    {
        Student* s = static_cast<Student*>(u);
        if (s->getAssignedPass()) 
        {
            s->getAssignedPass()->displayPassDetails();
        } 
        else 
        {
            ConsoleUI::printInfo("No passes associated with this student account.");
        }
    }
}

void TransportManager::payPassFee(const string& passID) 
{
    TransportPass* p = findPass(passID);
    if (!p) {
        ConsoleUI::printError("Pass ID not found.");
        return;
    }
    if (p->getBill().getIsPaid()) {
        ConsoleUI::printInfo("Fee for this pass is already paid.");
        return;
    }
    p->getBill().markAsPaid();
    ConsoleUI::printSuccess("Payment processed successfully! Invoice marked as PAID.");
}

// Find the student, if a pass exist, then cancel it
void TransportManager::cancelRegistration(const string& studentUsername) 
{
    User* u = findUser(studentUsername);
    if (!u || u->getRole() != "Student") return;

    Student* s = static_cast<Student*>(u);
    TransportPass* pass = s->getAssignedPass();
    if (!pass) {
        ConsoleUI::printError("No registration found to cancel.");
        return;
    }

    // Release capacity on the assigned vehicle if approved
    if (!pass->getVehicleID().empty()) {
        Vehicle* v = findVehicle(pass->getVehicleID());
        if (v) {
            v->decrementPassengers();
        }
    }

    // Remove from passList
    for (int i = 0; i < passList.getSize(); ++i) {
        if (passList[i]->getPassID() == pass->getPassID()) {
            delete passList[i];
            passList.remove(i);
            break;
        }
    }

    s->unlinkPass();
    ConsoleUI::printSuccess("Transport pass registration cancelled successfully.");
}

// helper functions 
User* TransportManager::findUser(const string& username) const 
{
    for (int i = 0; i < userList.getSize(); ++i) 
    {
        if (userList[i]->getUsername() == username) 
        {
            return userList[i];
        }
    }
    return nullptr;
}
Vehicle* TransportManager::findVehicle(const string& vehicleID) const {
    for (int i = 0; i < vehicleList.getSize(); ++i) {
        if (vehicleList[i]->getVehicleID() == vehicleID) {
            return vehicleList[i];
        }
    }
    return nullptr;
}
Route* TransportManager::findRoute(const string& routeID) const {
    for (int i = 0; i < routeList.getSize(); ++i) {
        if (routeList[i]->getRouteID() == routeID) {
            return routeList[i];
        }
    }
    return nullptr;
}
TransportPass* TransportManager::findPass(const string& passID) const {
    for (int i = 0; i < passList.getSize(); ++i) {
        if (passList[i]->getPassID() == passID) {
            return passList[i];
        }
    }
    return nullptr;
}
const ClassArray<User*>& TransportManager::getUserList() const { return userList; }





int TransportManager::getUserCount() const { return userList.getSize(); }

const ClassArray<Vehicle*>& TransportManager::getVehicleList() const { return vehicleList; }

int TransportManager::getVehicleCount() const { return vehicleList.getSize(); }

const ClassArray<Route*>& TransportManager::getRouteList() const { return routeList; }

int TransportManager::getRouteCount() const { return routeList.getSize(); }

const ClassArray<TransportPass*>& TransportManager::getPassList() const { return passList; }

int TransportManager::getPassCount() const { return passList.getSize(); }

// Date calculations utility function
static string getNextMonthDate(const string& dateStr) {
    if (dateStr.length() != 10) return "2026-07-01";
    try {
        int y = stoi(dateStr.substr(0, 4));
        int m = stoi(dateStr.substr(5, 2));
        int d = stoi(dateStr.substr(8, 2));
        m++;
        if (m > 12) {
            m = 1;
            y++;
        }
        char buf[12];
        sprintf(buf, "%04d-%02d-%02d", y, m, d);
        return string(buf);
    } catch (...) {
        return "2026-07-01";
    }
}