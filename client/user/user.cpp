#include "user.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <numeric>
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
    long long int hashedPassword = 0;
    for (char i : password) {
        hashedPassword += (i * 10) % 177;
        hashedPassword += i;
        hashedPassword *= 3;
    }

    srand(hashedPassword);
    unsigned long long randNum = (rand() % (1000) * rand() % (1000) * rand() % (1000) * rand() % (1000) * rand() % (1000));
    hashedPassword *= randNum;

    srand(hashedPassword);
    randNum = (rand() % (1000) * rand() % (1000) * rand() % (1000) * rand() % (1000) * rand() % (1000));
    hashedPassword *= randNum;

    return std::to_string(hashedPassword);
}
