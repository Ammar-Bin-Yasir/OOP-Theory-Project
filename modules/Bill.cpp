#include "modules/Bill.h"
#include "core/ConsoleUI.h"
#include <iostream>

using namespace std;

Bill::Bill() : monthlyFee(0.0), lateFine(0.0), isPaid(false), dueDate("") {}

Bill::Bill(double fee, string due)
    : monthlyFee(fee), lateFine(0.0), isPaid(false), dueDate(due) {}

Bill::Bill(double fee, double fine, string due, bool paidStatus)
    : monthlyFee(fee), lateFine(fine), isPaid(paidStatus), dueDate(due) {}

double Bill::getMonthlyFee() const {
    return monthlyFee;
}

double Bill::getLateFine() const {
    return lateFine;
}

double Bill::getTotalAmount() const {
    return monthlyFee + lateFine;
}

bool Bill::getIsPaid() const {
    return isPaid;
}

string Bill::getDueDate() const {
    return dueDate;
}

void Bill::markAsPaid() {
    isPaid = true;
    lateFine = 0.0; // Reset fine upon payment
}

void Bill::setPaidStatus(bool paidStatus) {
    isPaid = paidStatus;
}

void Bill::applyLateFine(double fineAmount) {
    lateFine += fineAmount;
}

void Bill::displayBill() const {
    ConsoleUI::printLabelValue("Monthly Fee Amount", "Rs. " + ConsoleUI::formatDouble(monthlyFee));
    ConsoleUI::printLabelValue("Accumulated Fine", "Rs. " + ConsoleUI::formatDouble(lateFine));
    ConsoleUI::printLabelValue("Total Outstanding", "Rs. " + ConsoleUI::formatDouble(getTotalAmount()));
    ConsoleUI::printLabelValue("Payment Due Date", dueDate);
    ConsoleUI::printLabelValue("Payment Status", isPaid ? (ConsoleUI::GREEN + "PAID" + ConsoleUI::RESET) : (ConsoleUI::RED + "UNPAID" + ConsoleUI::RESET));
}
