#ifndef VAN_H
#define VAN_H

#include "core/Vehicle.h"

class Van : public Vehicle 
{
    public:
        // Constructor
        Van(std::string id, std::string routeID);
        
        // Destructor
        ~Van() override = default;

        // Polymorphic Overrides
        double calculateMaintenance() const override;
        void displayDetails() const override;

        virtual std::string toCSV() const = 0;
};

#endif