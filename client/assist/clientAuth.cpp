#include "../user/user.h"
#include "../user/userCred.h"
#include "clientAuth.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <functional>
#include <thread>

ClientAuth::ClientAuth(int clientSocket, int serverPort, std::string serverDomainName) {
    this->authSocket = clientSocket + 1;
    this->serverPort = serverPort;
    this->serverDomainName = serverDomainName;

    authSocket = socket(AF_INET, SOCK_STREAM, 0); 
    if (authSocket == -1) {
        std::cerr << "Error creating socket." << std::endl;
    }

    struct sockaddr_in serverAddr;
    struct hostent* serverInfo;

    //Domain name to  IP address
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

    while(true) {
        while (true) {
            std::cout << "Register(0) or Login(1): ";
            std::cin >> choice;

            if (choice == "0" || choice == "1") {
                break;
            } 
            else {
                std::cout << "Invalid input. Please enter a valid choice." << std::endl;
                std::cin.clear(); //clears error state
                std::cin.ignore(); //discards input buffer
            }
        }
        //Calls InputCredentials from userCred to ask user to input username and password
        credentials.InputCredentials(std::cout, std::cin);

        this->authenticationUser = credentials.GetUser();
        if (choice == "0") {
            if (!Register()) { 
                std::cout << "This user already exists, please login instead." << std::endl; 
                exit(0);
            }
            std::cout << "Registration successful!" << std::endl;
            return;
        }
        else {
            if (!Login()) { 
                std::cout << "Username or password not recognized.\n";
                exit(0);
            }
            std::cout << "Login successful!" << std::endl;
            return;
        }
    }

}

//This is where we can have the message to be sent to server 
bool ClientAuth::Register() {
    //ALWAYS START REGISTER WITH A 0 AND END WITH A NEWLINE OR IT WONT WORK RIGHT
    //puts the username/password into a single message
    std::string login = loginString();
    char* message = new char[login.length() + 1];
    message[0] = '0';
    int j = 1;

    for (char i : login) {
        message[j] = i;
        ++j;
    }
    message[login.length()] = '\0'; //Stores null terminator character

    //sends the message to the server
    int messageLength = strlen(message);
    int bytesSent = send(authSocket, message, messageLength, 0);
    if (bytesSent == -1) {
        std::cerr << "Error sending message." << std::endl;
        delete [] message;
        return false;
    }
    delete [] message;
    return ServerResponse();
}

bool ClientAuth::Login() {
    //ALWAYS START LOGIN WITH A 1 AND END WITH A NEWLINE OR IT WONT WORK RIGHT
    //puts the username/password into a single message
    std::string login = loginString();
    char *message = new char[login.length() + 1];
    message[0] = '1';
    int j = 1;

    for (char i : login) {
        message[j] = i;
        ++j;
    }
    message[login.length()] = '\0';

    //sends the message to the server
    int messageLength = strlen(message);
    int bytesSent = send(authSocket, message, messageLength, 0);
    if (bytesSent == -1) {
        std::cerr << "Error sending message." << std::endl;
        delete [] message;
        return false;
    }
    delete [] message;
    return ServerResponse();
}

bool ClientAuth::ServerResponse() {
    //logic to take input for use in the prompt method of client authenticator
    //server only responds with a single character
    char success[2];
    recv(authSocket, success, sizeof(success), 0);

    if (success[0] == '1') {
        return true;
    }
    else {
        return false;
    }
    return false;
}


User ClientAuth::GetUser(){
    return this->authenticationUser;
}

std::string ClientAuth::loginString()
{
    //Sends login information in a specific format
    std::string login;
    login.append(authenticationUser.GetUsername());
    login.push_back(17);
    login.append(authenticationUser.GetPassword());
    login.push_back('\n');
    return login;
}