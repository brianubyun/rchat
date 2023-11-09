#include "user.h"
#include <iostream>

User::User() {}

User::~User() {}

void User::SetUsername(std::string username) {
    this->username = username;
}

void User::SetPassword(std::string password) {
    this->password = password;
}

std::string User::GetUsername() {
    return this->username;
}

std::string User::GetPassword() {
    return this->password;
}