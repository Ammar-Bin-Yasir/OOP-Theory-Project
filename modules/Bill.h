/* Each bill will be composed inside of TransportPass class which is associated with each passenger. 
    The bill does not exist independently; it calculates the monthly bill for the registered passenger. */
    
#ifndef BILL_H
#define BILL_H

#include <string>

class Bill {
private:
    double monthlyFee;
    double lateFine;
    bool isPaid;
    std::string dueDate;

public:
    // 1. Default Constructor (Initializes blank fields for safety)
    Bill();

    // 2. Standard Interactive Constructor (Used when an Admin creates a new pass request)
    Bill(double fee, std::string due);

    // 3. Complete Reconstruction Constructor (Crucial for File Loading without data loss)
    Bill(double fee, double fine, std::string due, bool paidStatus);

    
    ~Bill() = default;

    // Getters (Essential for Pass-Level Serialization and Engine Reporting)
    double getMonthlyFee() const;
    double getLateFine() const;
    double getTotalAmount() const; // Returns monthlyFee + lateFine
    bool getIsPaid() const;
    std::string getDueDate() const;

    // Business Logic Methods
    void markAsPaid();
    void setPaidStatus(bool paidStatus);
    void applyLateFine(double fineAmount);
    void displayBill() const;
};

#endif