#ifndef USER_H
#define USER_H

#include <string>

// Forward declaration to avoid circular dependency
class TransportManager; 

class User 
{
    private:
        std::string username, password, role;
    
    // Base classes will inherit these
    public:
        // Constructors
        User(const std::string& username, const std::string& password, const std::string& role);
        
        // Destructor
        virtual ~User() = default;

        // These are inherited by both Admin and Passenger so both can access but cannot modify
        std::string getUsername() const;
        std::string getRole() const;

        // setter for password with validation
        void changePassword(const std::string& oldPassword, const std::string& newPassword);
        bool checkPassword(const std::string& input) const;
        
    
        // Pure Virtual function to be implemented by derived classes
        virtual void showMenu(TransportManager& manager) = 0;
        
        virtual std::string toCSV() const = 0;
};

#endif 