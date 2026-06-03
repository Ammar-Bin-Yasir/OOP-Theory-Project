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
    if (checkPassword(oldPassword)) {
        password = newPassword;
    }
}

bool User::checkPassword(const string& input) const {
    return this->password == input;
}

string User::getPassword() const {
    return password;
}
