#include "storage/FileHandler.h"
#include "Engine/TransportManager.h"
#include <iostream>

using namespace std;

FileHandler::FileHandler(const string& uPath, const string& vPath, const string& rPath, const string& pPath)
    : usersFilePath(uPath), vehiclesFilePath(vPath), routesFilePath(rPath), passesFilePath(pPath) {}

void FileHandler::loadRoutes(TransportManager& manager) {
    // Empty stub
}

void FileHandler::loadVehicles(TransportManager& manager) {
    // Empty stub
}

void FileHandler::loadUsers(TransportManager& manager) {
    // Empty stub
}

void FileHandler::loadPasses(TransportManager& manager) {
    // Empty stub
}

void FileHandler::loadAllData(TransportManager& manager) {
    // Empty stub
}

void FileHandler::saveAllData(const TransportManager& manager) {
    // Empty stub
}
