#include "user.h"
#include <iostream>

User::User() {}

User::~User() {}

void User::SetUsername(std::string username) {
    this->username = username;
}

void User::SetUsername(std::string password) {
    this->password = password;
}

string User::GetUsername() {
    return this->username;
}

string User::GetPassword() {
    return this->password;
}