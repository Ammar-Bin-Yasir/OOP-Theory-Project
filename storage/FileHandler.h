#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
class TransportManager;

class FileHandler {
private:
    std::string usersFilePath, vehiclesFilePath, routesFilePath, passesFilePath;

    void loadRoutes(TransportManager& manager);
    void loadVehicles(TransportManager& manager);
    void loadUsers(TransportManager& manager);
    void loadPasses(TransportManager& manager);
public:
    FileHandler(const std::string& uPath, const std::string& vPath, const std::string& rPath, const std::string& pPath);    
    ~FileHandler() = default;

    // Population Methods: Read from files and use manager methods to re-allocate models
    void loadAllData(TransportManager& manager);

    // Extraction Methods: Read data structures from manager arrays and format back to raw lines
    void saveAllData(const TransportManager& manager);
};

#endif