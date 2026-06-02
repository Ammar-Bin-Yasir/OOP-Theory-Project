#ifndef VAN_H
#define VAN_H

#include "core/Vehicle.h"

class Van : public Vehicle 
{
    public:
        // Constructor
        Van(std::string id, std::string routeID, int capacity = 15);
        
        // Destructor
        ~Van() override = default;

        // Polymorphic Overrides
        double calculateMaintenance() const override;
        void displayDetails() const override;

        std::string toCSV() const override;
};

#endif