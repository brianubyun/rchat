#include "user/user.h"
#include "user/userCred.h"
#include "assist/clientAuth.h"
#include "client.h"
#include "client_command_handler.h"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MAXBYTES 4096

Client::Client() {
    isRunning = true;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    killThreads = false;
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
    std::string user = authenticator.GetUser().GetUsername();

    std::thread sendThread(&Client::SendLoop, this, user);
    std::thread receiveThread(&Client::ReceiveLoop, this);

    receiveThread.join();
    sendThread.join();
    
}

void Client::SendLoop(std::string username) { 
    while (isRunning) {
        char buffer[MAXBYTES] = {0};
        //Prompt the user for input and read it into the buffer
        //std::cout << "Enter a message: ";
        //Code relating to the select function (namely lines 66-77) were adapted from this stackoverflow post: https://stackoverflow.com/a/9732927
        //select needs a file descriptor set, and a timeval
        struct timeval tv;
        tv.tv_sec = 3; //seconds
        tv.tv_usec = 0; //milliseconds
        fd_set fds; //declares the file descriptor set
        FD_ZERO (&fds); //initializes the file descriptor set
        FD_SET (STDIN_FILENO, &fds); 
        if(!(select (STDIN_FILENO + 1, &fds, NULL, NULL, &tv))){
            if(killThreads)
            {
                return;
            }
            continue;
        }
        std::cin.getline(buffer, MAXBYTES);
        if(strlen(buffer) == 0) {
            continue;
        }
        //Continue or end client
        if (std::string(buffer) == "//quit") {
            killThreads = true;
            char message[2] = "0";
            SendMessage(message);
            return;
        }
        std::string unprocessedMessage = std::string(buffer);
        ClientCommandHandler handler;
        std::string message = handler.HandleCommand(unprocessedMessage);
        message = username + ": " + message;
        SendMessage(message.c_str());
    }
}

void Client::ReceiveLoop() {
    char buffer[MAXBYTES];
    while (true) {
        if(killThreads) {
            return;
        }

        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << std::endl << "Connection to the server closed." << std::endl;
            killThreads = true;
            return;
        }

        std::string message(buffer, bytesRead);
        if(message.at(0) == 18) {
            char endMsg[2];
            endMsg[1] = (char)(17);
            endMsg[2] = '\0';
            SendMessage(endMsg);
            killThreads = true;
            return;
        }
        std::cout << message << std::endl << std::endl;
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
    isRunning = false;
    close(clientSocket);
}

