#ifndef TRANSPORTPASS_H
#define TRANSPORTPASS_H

#include <string>
#include "modules/Bill.h" 

class TransportPass 
{
    private:
        std::string passID, studentUsername, routeID, vehicleID, status;
        
        // COMPOSITION: Embedded instance
        Bill invoice; 

    public:
        // Constructors & Destructor
        TransportPass();
        TransportPass(std::string pID, std::string sUname, std::string rID, std::string vID, double baseFee, std::string due);
        TransportPass(std::string csvLine); // File parsing constructor
        ~TransportPass() = default;

        // Getters
        std::string getPassID() const;
        std::string getStudentUsername() const;
        std::string getRouteID() const;
        std::string getVehicleID() const;
        std::string getStatus() const;
        
        // Controlled gateway to the composed instance
        Bill& getBill(); 

        // Setters / Status Updates
        void setStatus(std::string newStatus);
        void assignVehicle(std::string vID);
        
        // Display and Serialization Methods
        void displayPassDetails() const;
        std::string toCSV() const;
};

#endif