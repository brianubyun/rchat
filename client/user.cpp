#include "client.h"
#include <iostream>

User::user() {}

User::~User() {}

void User::setUsername(std::string username) {
    this->username = username;
}

void User::setUsername(std::string password) {
    this->password = password;
}

string User::getUsername() {
    return this->username;
}

string User::setUsername() {
    return this->password;
}