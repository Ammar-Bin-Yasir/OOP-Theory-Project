#include "core/User.h"
#include "Engine/TransportManager.h"

using namespace std;

User::User(const string& username, const string& password, const string& role) 
    : username(username), password(password), role(role) {}

string User::getUsername() const {
    return username;
}

string User::getRole() const {
    return role;
}

void User::changePassword(const string& oldPassword, const string& newPassword) {
    // Stub
}

bool User::checkPassword(const string& input) const {
    return false; // Stub
}

string User::toCSV() const {
    return username + "," + password + "," + role;
}
