#include "stubUser.h"
#include <string>
#include <iostream>

stubUser::stubUser() {
    username = "Brian";
    password = "Byun"; //Test parameters, remove these later when User Class is implemented
}

stubUser::~stubUser() {
    std::cout << "Destructor called." << std::endl;
}

std::string stubUser::getUsername() const {
    return username;
}

std::string stubUser::getPassword() const {
    return password;
}

bool stubUser::Register() { 
    return true;
}

void stubUser::Login() {
    std::cout << "User " << username << " logged in." << std::endl;
}