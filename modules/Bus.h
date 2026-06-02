#ifndef BUS_H
#define BUS_H

#include "core/Vehicle.h"

class Bus : public Vehicle 
{
    public:
        // Constructor
        Bus(std::string id, std::string routeID, int capacity = 40);
        
        // Destructor
        ~Bus() override = default;

        // Polymorphic Overrides
        double calculateMaintenance() const override;
        void displayDetails() const override;

        std::string toCSV() const override;
};

#endif