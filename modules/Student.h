#ifndef STUDENT_H
#define STUDENT_H
#include "core/User.h"

// Forward declarations to avoid circular dependencies
class TransportPass; 
class TransportManager; 

class Student : public User {
    private:
        std::string rollNumber;
        
        // ticket of the bus/van student has applied for and been assigned
        TransportPass* assignedPass; 
    public:
        // Constructor
        Student(const std::string& username, const std::string& password, const std::string& rollNumber);

        // Destructor
        ~Student() override = default;

        // We just want to get the roll number and assigned pass, we don't want to modify them directly from outside the class
        std::string getRollNumber() const;
        TransportPass* getAssignedPass() const;

        /* this function will link the pass to the student 
        from the files when program starts */
        void linkPass(TransportPass* pass);
        void unlinkPass(); 

        virtual std::string toCSV() const = 0;

        void showMenu(TransportManager& manager) override;
};

#endif