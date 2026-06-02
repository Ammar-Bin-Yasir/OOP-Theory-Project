#include "modules/Admin.h"
#include "Engine/TransportManager.h"
#include <iostream>

using namespace std;

Admin::Admin(const string& username, const string& password)
    : User(username, password, "Admin") {}

void Admin::showMenu(TransportManager& manager) {
    // Stub
}

string Admin::toCSV() const {
    return ""; // Stub
}
