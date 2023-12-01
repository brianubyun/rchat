#include "user.h"
#include "userCred.h"
#include <iostream>

UserCred::UserCred() {}

UserCred::~UserCred() {}

void UserCred::InputCredentials(std::ostream &out, std::istream &in) {
    std::string username;
    std::string password;

    while (true) {
        out << "Username: ";
        in >> username;

        if (in.fail()) {
            out << "Invalid input. Please enter a valid string." << std::endl;
            in.clear(); //clears error state
            in.ignore(); //discards input buffer
        } 
        else {
            break; 
        }
    }

    while (true) {
        out << "Password: ";
        in >> password;

        if (in.fail()) {
            out << "Invalid input. Please enter a valid string." << std::endl;
            in.clear(); //clears error state
            in.ignore(); //discards input buffer
        } 
        else {
            break; 
        }
    }
    //Successful username and password
    credentialUser.SetUsername(username);
    credentialUser.SetPassword(password);

}

User UserCred::GetUser() {
    return this->credentialUser;
}