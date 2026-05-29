#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle 
{
    private:
        std::string vehicleID, assignedRouteID;
        int activePassengers, totalCapacity;     

    public:
        // Constructor and Destructor
        Vehicle(std::string id, int capacity, std::string routeID);
        virtual ~Vehicle() = default; 

        // Getters
        std::string getVehicleID() const;
        std::string getAssignedRouteID() const;
        int getTotalCapacity() const;
        int getActivePassengers() const;

        // Setters / Modifiers
        void setAssignedRouteID(std::string routeID);
        bool incrementPassengers();
        void decrementPassengers();

        // Pure Virtual Function: Forces Bus and Van to calculate maintenance differently
        virtual double calculateMaintenance() const = 0;

        // Pure Virtual Function: For polymorphic console printing
        virtual void displayDetails() const = 0;

        virtual std::string toCSV() const = 0;
};

#endif