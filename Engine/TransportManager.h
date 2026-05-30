#ifndef TRANSPORTMANAGER_H
#define TRANSPORTMANAGER_H

#include <string>

class User;
class Vehicle;
class Route;
class TransportPass;

class TransportManager 
{
    private:
        // 2-D array's to keep track of how many users, vehicles, routes and TransportPasses are in the system
        User** userList;
        Vehicle** vehicleList;
        Route** routeList;
        TransportPass** passList;

        // Current item counters
        int userCount;
        int vehicleCount;
        int routeCount;
        int passCount;

        // Boundary limit trackers before array doubling triggers
        int userCapacity;
        int vehicleCapacity;
        int routeCapacity;
        int passCapacity;

        // Internal helper methods for dynamic expansion 
        void growUserList();
        void growVehicleList();
        void growRouteList();
        void growPassList();

    public:
        TransportManager();
        ~TransportManager(); 

        // 
        void loadSystemData();
        void saveSystemData();

        // The first menu users see when they start the program
        void runMainMenu();

        // Login & Registration System
        User* verifyLogin(const std::string& username, const std::string& password) const;
        bool registerNewUser(const std::string& username, const std::string& password, const std::string& role, const std::string& details);

        // Getters 
        User** getUserList() const;
        int getUserCount() const;
        Vehicle** getVehicleList() const;
        int getVehicleCount() const;
        Route** getRouteList() const;
        int getRouteCount() const;
        TransportPass** getPassList() const;
        int getPassCount() const;

        // Admin Panel Methods
        void addVehicle(Vehicle* newVehicle);
        void addRoute(const Route& newRoute);
        void assignVehicleToRoute(const std::string& vehicleID, const std::string& routeID);
        void viewAllApplications() const;
        void processApplication(const std::string& passID, bool approve);
        
        // Student Panel Methods    
        void viewAllRoutes() const; 
        void submitApplication(const std::string& studentUsername, const std::string& routeID); 
        void cancelRegistration(const std::string& studentUsername); 


        // Financial Analytical Reporting Engine
        void generateRevenueReport() const;
        void generateRouteUsageReport() const;
};

#endif