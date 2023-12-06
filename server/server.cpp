#include "server.h"
#include "chatlogging.h"
#include "commandhandler.h"

#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <algorithm>
#include <fcntl.h>
#include "ServerAuthenticator.h"
#define MAXBYTES 4096

//initialize a socket for the server 
Server::Server() : isRunning(false){
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); //AF_INET ---> Address Family Internet, SOCK_STREAM -- > Stream Socket, 0 is for default so it uses TCP 
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    int optval = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));
    if (fcntl(serverSocket, F_SETFL, fcntl(serverSocket, F_GETFL) | O_NONBLOCK) < 0) {
        std::cerr << "Error creating server socket." << std::endl;
        exit(EXIT_FAILURE);
    }
}

//Will deconstruct the server using stop 
Server::~Server() {
    Stop();
}

//Binds the socket to a port and then begin to listen and accept clients 
void Server::Start() {
    if (isRunning) {
        std::cerr << "Server is already running." << std::endl;
        return;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port); 
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding server socket." << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening on server socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    isRunning = true;
    CommandHandler handler;
    std::thread commandThread;
    commandThread = std::thread(&CommandHandler::ListenFor, &handler, this);
    commandThread.detach(); 

    AcceptClients();
    isRunning = false;
    Stop();
}

//Stops the server and closes clients 
void Server::Stop() {
    if(isRunning) {
        return; 
    
    }
    //Closes all client sockets
    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);
    isRunning = false;
    exit(0);
}

//Creates threads for each client 
void Server::AcceptClients() {
    std::cout << "listening..." << std::endl;
    bool login = false;
    while (isRunning) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

        if (clientSocket == -1) {
            continue;  //Continue to accept other connections
        }
        //Authenticate that they are a user
        if (login) {
            login = false;
            std::thread authenticationThread(&Server::Authenticate, this, clientSocket);
            authenticationThread.detach();
        }
        else {
            login = true;
            clientSockets.push_back(clientSocket);
            std::thread clientThread(&Server::HandleClient, this, clientSocket);
            clientThread.detach();
        }

        if (!isRunning) {
            return;
        }
    }
}

//What the thread will do for each client 
void Server::HandleClient(int clientSocket) {
    char buffer[MAXBYTES];
    Logger chatLog;

    while (isRunning) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            break;
        }
        if (buffer[0] == '0') {
            break;
        }
        chatLog.logMessage(buffer);

        buffer[bytesReceived] = '\0'; //Ensure null-termination char
        std::cout << "Received from " << buffer << std::endl;

        BroadcastMessage(buffer, strlen(buffer), clientSocket);
    }

    close(clientSocket);
    clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), clientSocket), clientSockets.end());
}

void Server::BroadcastMessage(char* message, int messageLength, int sendClient) {
    //For client in clientsockets send the message to them
    for (int client : clientSockets) {
        if (client != sendClient) { //Avoids having their message broadcasted back to them
            send(client, message, messageLength, 0);
        }
    }
}

void Server::SimpleStop() {
    isRunning = false;
}

void Server::Authenticate(int clientSocket) {
    ServerAuthenticator auth;
    bool authenticated = auth.authUser(clientSocket);
    if (!authenticated) {
        return;
    }
    close(clientSocket);
}