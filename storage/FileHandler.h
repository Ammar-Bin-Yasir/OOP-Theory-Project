#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include "Engine/TransportManager.h"

class FileHandler {
private:
    std::string usersFilePath;
    std::string vehiclesFilePath;
    std::string routesFilePath;
    std::string passesFilePath;

public:
    FileHandler(std::string uPath, std::string vPath, std::string rPath, std::string pPath);
    
    ~FileHandler();

    // Population Methods: Read from files and use manager methods to re-allocate models
    void loadAllData(TransportManager& manager);

    // Extraction Methods: Read data structures from manager arrays and format back to raw lines
    void saveAllData(const TransportManager& manager);
};

#endif