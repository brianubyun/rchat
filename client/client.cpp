#include "user/user.h"
#include "user/userCred.h"
#include "assist/clientAuth.h"
#include "client.h"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MAXBYTES 4096

Client::Client() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket." << std::endl;
    }
}

Client::~Client() {
    close(clientSocket);
}

bool Client::Connect() {
    struct sockaddr_in serverAddr;
    struct hostent* serverInfo;

    // Resolve the domain name to an IP address
    serverInfo = gethostbyname(serverDomainName.c_str());
    if (serverInfo == nullptr) {
        std::cerr << "Error resolving host name." << std::endl;
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    memcpy(&serverAddr.sin_addr, serverInfo->h_addr, serverInfo->h_length);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to the server." << std::endl;
        return false;
    }
    return true;
}

void Client::Start() {
    ClientAuth authenticator(clientSocket, serverPort, serverDomainName);
    authenticator.Prompt();

    std::thread sendThread(&Client::SendLoop, this);
    std::thread receiveThread(&Client::ReceiveLoop, this);

    //Join threads
    sendThread.join();
    receiveThread.join();
}

void Client::SendLoop() { 
    while (true) {
        char buffer[MAXBYTES];

        // Prompt the user for input and read it into the buffer
        //std::cout << "Enter a message: ";
        std::cin.getline(buffer, MAXBYTES);

        // User sent //quit command and exits chat 
        if (std::string(buffer) == "//quit") {  
            SendMessage("Connection closed. Client disconnected.");
            exit(0); //Terminates program since chat program is exited
            std::cin.clear(); //Clears buffer
        }

        // Send the message from the buffer since //quit was not inputted
        SendMessage(buffer);
    }
}

void Client::ReceiveLoop() {
    char buffer[MAXBYTES];

    while (true) {
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << std::endl << "Connection to the server closed." << std::endl;
            exit(0);
        }

        std::string message(buffer, bytesRead);
        std::cout << "Received message: " << message << std::endl << std::endl;
    }
}  

void Client::SendMessage(const char* message) {
    int messageLength = strlen(message);
    int bytesSent = send(clientSocket, message, messageLength, 0);
    
    if (bytesSent == -1) {
        std::cerr << "Error sending message." << std::endl;
    }
}

void Client::Disconnect() {
    close(clientSocket);
}

