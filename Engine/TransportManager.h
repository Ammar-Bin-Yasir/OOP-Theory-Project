#ifndef TRANSPORTMANAGER_H
#define TRANSPORTMANAGER_H

#include <string>
#include "core/ClassArray.h"

class User;
class Vehicle;
class Route;
class TransportPass;

class TransportManager 
{
    friend class FileHandler;
    private:
        ClassArray<User*> userList;
        ClassArray<Vehicle*> vehicleList;
        ClassArray<Route*> routeList;
        ClassArray<TransportPass*> passList;

        std::string currentSystemDate;

    public:
        // Constructor Destructor
        TransportManager();
        ~TransportManager(); 

        // Load Save Data
        void loadSystemData();
        void saveSystemData();

        // The first menu users see when they start the program
        void runMainMenu();

        // Login & Registration System
        User* verifyLogin(const std::string& username, const std::string& password) const;
        bool registerNewUser(const std::string& username, const std::string& password, const std::string& role, const std::string& details);
        
        // Admin Panel Methods
        void addVehicle(Vehicle* newVehicle);
        void updateVehicleDetails(const std::string& vehicleID, int newCapacity, const std::string& newRouteID);
        void removeVehicle(const std::string& vehicleID);
        void viewAllVehicles() const;
        void addRoute(const Route& newRoute);
        void assignVehicleToRoute(const std::string& vehicleID, const std::string& routeID);
        void viewAllApplications() const;
        void processApplication(const std::string& passID, bool approve);
        
        // Financial Analytical Reporting Engine (For admin)
        void generateRouteUsageReport() const;
        void generateRevenueReport() const;
        
        // Date & Billing Cycle Management (For Admin)
        std::string getSystemDate() const;
        void setSystemDate(const std::string& newDate);
        void advanceBillingCycle();
        
        // Student Panel Methods    
        void viewAvailableRoutes() const; 
        void submitApplication(const std::string& studentUsername, const std::string& routeID); 
        void viewMyApplications(const std::string& studentUsername) const;
        void payPassFee(const std::string& passID);
        void cancelRegistration(const std::string& studentUsername); 
        
        // Search & Lookup Helpers
        User* findUser(const std::string& username) const;
        Vehicle* findVehicle(const std::string& vehicleID) const;
        Route* findRoute(const std::string& routeID) const;
        TransportPass* findPass(const std::string& passID) const;
        
        
        // Getters 
        const ClassArray<User*>& getUserList() const;
        int getUserCount() const;
        const ClassArray<Vehicle*>& getVehicleList() const;
        int getVehicleCount() const;
        const ClassArray<Route*>& getRouteList() const;
        int getRouteCount() const;
        const ClassArray<TransportPass*>& getPassList() const;
        int getPassCount() const;
};

#endif