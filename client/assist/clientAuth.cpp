#include "../user/user.h"
#include "../user/userCred.h"
#include "clientAuth.h"


#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <functional>
#include <thread>

ClientAuth::ClientAuth(int clientSocket, int serverPort, std::string serverDomainName) {
    this -> authSocket = clientSocket + 1;
    this -> serverPort = serverPort;
    this -> serverDomainName = serverDomainName;

    authSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (authSocket == -1) {
        std::cerr << "Error creating socket." << std::endl;
    }

    struct sockaddr_in serverAddr;
    struct hostent* serverInfo;

    // Resolve the domain name to an IP address
    serverInfo = gethostbyname(serverDomainName.c_str());
    if (serverInfo == nullptr) {
        std::cerr << "Error resolving host name." << std::endl;
        exit(0);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    memcpy(&serverAddr.sin_addr, serverInfo->h_addr, serverInfo->h_length);

    if (connect(authSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to the server." << std::endl;
        exit(0);
    }

}

ClientAuth::~ClientAuth() {}

void ClientAuth::Prompt() {

    std::string choice;
    UserCred credentials;


    while (true) {

        std::cout << "Register(0) or Login(1): ";
        std::cin >> choice;

        if (choice == "0" || choice == "1") {
            break; // Exit the loop if a valid integer is entered
            
        } 
        
        else {
            std::cout << "Invalid input. Please enter a valid choice." << std::endl;
            std::cin.clear(); // Clear the error state
            std::cin.ignore(); // Discard the input buffer
        }
    }

    credentials.InputCredentials();

    this->authenticationUser = credentials.GetUser();

    if (choice == "0"){
        Register();
    }

    else {
        //Login();
    }


}

//This is where we can have the message to be sent to server 
/*
bool ClientAuth::Register() {
    char message[] = "test";
    int messageLength = strlen(message);
    int bytesSent = send(authSocket, message, messageLength, 0);
    if (bytesSent == -1) {
        std::cerr << "Error sending message." << std::endl;
        return false;
    }
    return true;
}


bool ClientAuth::Login() {
    //logic to take input for use in the prompt method of client authenticator
}

bool ClientAuth::ServerResponse() {
    //logic to take input for use in the prompt method of client authenticator
}

*/

User ClientAuth::GetUser(){
    return this->authenticationUser;
}