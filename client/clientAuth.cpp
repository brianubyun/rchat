#include "user.h"
#include "userCred.h"
#include "clientAuth.h"
#include <iostream>

ClientAuth::ClientAuth() {}

ClientAuth::~ClientAuth() {}

void ClientAuth::Prompt() {

    std::string choice;
    UserCred credentials;


    while (true) {

        std::cout << "Register(0) or Login(1): ";
        std::cin >> choice;

        if (choice != "0" || choice != "1") {
            cout << "Invalid input. Please enter a valid string." << endl;
            std::cin.clear(); // Clear the error state
            std::cin.ignore(); // Discard the input buffer
        } 
        
        else {
            break; // Exit the loop if a valid integer is entered
        }
    }

    credentials.InputCredentials();

    this->authenticationUser = credentials.GetUser();

    if (choice == "1"){
        Register();
    }

    else {
        Login();
    }


}

bool ClientAuth::Register() {
    //logic to take input for use in the prompt method of client authenticator
}

bool ClientAuth::Login() {
    //logic to take input for use in the prompt method of client authenticator
}

bool ClientAuth::ServerResponse() {
    //logic to take input for use in the prompt method of client authenticator
}


User ClientAuth::GetUser(){
    return this->credentialUser;
}