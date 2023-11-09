#include "user/user.h"
#include "userCred.h"
#include <iostream>

UserCred::UserCred() {}

UserCred::~UserCred() {}

void UserCred::InputCredentials() {
    
    std::string username;
    std::string password;

    while (true) {

        std::cout << "Username: ";
        std::cin >> username;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a valid string." << std::endl;
            std::cin.clear(); // Clear the error state
            std::cin.ignore(); // Discard the input buffer
        } 
        
        else {
            break; // Exit the loop if a valid integer is entered
        }
    }

    while (true) {
        std::cout << "Password: ";
        std::cin >> password;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a valid string." << std::endl;
            std::cin.clear(); // Clear the error state
            std::cin.ignore(); // Discard the input buffer
        } 
        
        else {
            break; // Exit the loop if a valid integer is entered
        }
    }

    credentialUser.SetUsername(username);
    credentialUser.SetPassword(password);

}

User UserCred::GetUser(){
    return this->credentialUser;
}