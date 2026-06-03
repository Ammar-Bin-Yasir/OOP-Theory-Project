#include "storage/FileHandler.h"
#include "Engine/TransportManager.h"
#include "core/User.h"
#include "modules/Student.h"
#include "modules/Admin.h"
#include "core/Vehicle.h"
#include "modules/Bus.h"
#include "modules/Van.h"
#include "modules/Route.h"
#include "modules/TransportPass.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

FileHandler::FileHandler(const string& uPath, const string& vPath, const string& rPath, const string& pPath)
    : usersFilePath(uPath), vehiclesFilePath(vPath), routesFilePath(rPath), passesFilePath(pPath) {}

static void trimCR(string& s) {
    if (!s.empty() && s.back() == '\r') {
        s.pop_back();
    }
}

void FileHandler::loadRoutes(TransportManager& manager) {
    ifstream file(routesFilePath);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Route* r = new Route(line);
        manager.routeList.add(r);
    }
    file.close();
}

void FileHandler::loadVehicles(TransportManager& manager) {
    ifstream file(vehiclesFilePath);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string type, id, routeID, capStr, actStr;
        
        getline(ss, type, ',');
        getline(ss, id, ',');
        getline(ss, routeID, ',');
        getline(ss, capStr, ',');
        getline(ss, actStr, ',');

        trimCR(type);
        trimCR(id);
        trimCR(routeID);
        trimCR(capStr);
        trimCR(actStr);

        int cap = 40;
        int act = 0;
        try { cap = stoi(capStr); } catch (...) {}
        try { act = stoi(actStr); } catch (...) {}

        Vehicle* v = nullptr;
        if (type == "Bus") {
            v = new Bus(id, routeID, cap);
        } else if (type == "Van") {
            v = new Van(id, routeID, cap);
        }

        if (v) {
            for (int i = 0; i < act; ++i) {
                v->incrementPassengers();
            }
            manager.vehicleList.add(v);
        }
    }
    file.close();
}

void FileHandler::loadUsers(TransportManager& manager) {
    ifstream file(usersFilePath);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string role, username, password, details;
        
        getline(ss, role, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, details, ',');

        trimCR(role);
        trimCR(username);
        trimCR(password);
        trimCR(details);

        if (role == "Admin") {
            manager.userList.add(new Admin(username, password));
        } else if (role == "Student") {
            manager.userList.add(new Student(username, password, details));
        }
    }
    file.close();
}

void FileHandler::loadPasses(TransportManager& manager) {
    ifstream file(passesFilePath);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        TransportPass* pass = new TransportPass(line);
        manager.passList.add(pass);

        // Restore pass association to Student object
        User* u = manager.findUser(pass->getStudentUsername());
        if (u && u->getRole() == "Student") {
            Student* s = static_cast<Student*>(u);
            s->linkPass(pass);
        }
    }
    file.close();
}

void FileHandler::loadAllData(TransportManager& manager) {
    // Prevent memory leaks if reloading data
    for (int i = 0; i < manager.userList.getSize(); ++i) delete manager.userList[i];
    for (int i = 0; i < manager.vehicleList.getSize(); ++i) delete manager.vehicleList[i];
    for (int i = 0; i < manager.routeList.getSize(); ++i) delete manager.routeList[i];
    for (int i = 0; i < manager.passList.getSize(); ++i) delete manager.passList[i];

    manager.userList = ClassArray<User*>();
    manager.vehicleList = ClassArray<Vehicle*>();
    manager.routeList = ClassArray<Route*>();
    manager.passList = ClassArray<TransportPass*>();

    loadRoutes(manager);
    loadVehicles(manager);
    loadUsers(manager);
    loadPasses(manager);
}

void FileHandler::saveAllData(const TransportManager& manager) {
    // 1. Save Routes
    ofstream rFile(routesFilePath);
    if (rFile.is_open()) {
        for (int i = 0; i < manager.routeList.getSize(); ++i) {
            rFile << manager.routeList[i]->toCSV() << "\n";
        }
        rFile.close();
    }

    // 2. Save Vehicles
    ofstream vFile(vehiclesFilePath);
    if (vFile.is_open()) {
        for (int i = 0; i < manager.vehicleList.getSize(); ++i) {
            vFile << manager.vehicleList[i]->toCSV() << "\n";
        }
        vFile.close();
    }

    // 3. Save Users
    ofstream uFile(usersFilePath);
    if (uFile.is_open()) {
        for (int i = 0; i < manager.userList.getSize(); ++i) {
            uFile << manager.userList[i]->toCSV() << "\n";
        }
        uFile.close();
    }

    // 4. Save Passes
    ofstream pFile(passesFilePath);
    if (pFile.is_open()) {
        for (int i = 0; i < manager.passList.getSize(); ++i) {
            pFile << manager.passList[i]->toCSV() << "\n";
        }
        pFile.close();
    }
}
