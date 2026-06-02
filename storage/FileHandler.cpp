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
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

FileHandler::FileHandler(const string& uPath, const string& vPath, const string& rPath, const string& pPath)
    : usersFilePath(uPath), vehiclesFilePath(vPath), routesFilePath(rPath), passesFilePath(pPath) {}

void FileHandler::loadRoutes(TransportManager& manager) {
    // Stub
}

void FileHandler::loadVehicles(TransportManager& manager) {
    // Stub
}

void FileHandler::loadUsers(TransportManager& manager) {
    // Stub
}

void FileHandler::loadPasses(TransportManager& manager) {
    // Stub
}

void FileHandler::loadAllData(TransportManager& manager) {
    // Stub
}

void FileHandler::saveAllData(const TransportManager& manager) {
    // Stub
}
