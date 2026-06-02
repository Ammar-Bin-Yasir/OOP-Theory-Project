#include "modules/Student.h"
#include "modules/TransportPass.h"
#include "Engine/TransportManager.h"
#include <iostream>

using namespace std;

Student::Student(const string& username, const string& password, const string& rollNumber)
    : User(username, password, "Student"), rollNumber(rollNumber), assignedPass(nullptr) {}

string Student::getRollNumber() const {
    return rollNumber;
}

TransportPass* Student::getAssignedPass() const {
    return assignedPass;
}

void Student::linkPass(TransportPass* pass) {
    assignedPass = pass;
}

void Student::unlinkPass() {
    assignedPass = nullptr;
}

string Student::toCSV() const {
    return ""; // Empty stub
}

void Student::showMenu(TransportManager& manager) {
    // Empty stub
}
