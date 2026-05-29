#ifndef ADMIN_H
#define ADMIN_H

#include "core/User.h"

class TransportManager; 
class Admin : public User 
{
    public:
        // Constructor
        Admin(const std::string& username, const std::string& password);

        // Destructor
        ~Admin() override = default;

        // Override the pure virtual function to render the administrative operations
        void showMenu(TransportManager& manager) override;

        virtual std::string toCSV() const = 0;
};

#endif 