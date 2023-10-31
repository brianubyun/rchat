#include "server.h"
#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <algorithm>

using namespace std;
#define MAXBYTES 4096


//initialize a socket for the server 
Server::Server() : isRunning(false) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);//AF_INET ---> Address Family Internet, SOCK_STREAM -- > Stream Socket, 0 is for default so it uses TCP 
    if (serverSocket == -1) {
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
    AcceptClients();
}

//Stops the server and closes clients 
void Server::Stop() {
    if (!isRunning) {
        return;
    }

    // Close all client sockets
    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);
    isRunning = false;
}

//Creates threads for each client 
void Server::AcceptClients() {
    std::cout << "listening..." << std::endl;
    while (isRunning) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

        if (clientSocket == -1) {
            std::cerr << "Error accepting client connection." << std::endl;
            continue;  // Continue to accept other connections
        }

        clientSockets.push_back(clientSocket);

        std::thread clientThread(&Server::HandleClient, this, clientSocket);
        clientThread.detach();  // Detach the thread to run independently
    }
}

//What the thread will do for each client 
void Server::HandleClient(int clientSocket) {
    char buffer[MAXBYTES];
    while (true) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            // Handle client disconnection or error
            break;
        }

        // Process the received data (in this example, we just print it)
        buffer[bytesReceived] = '\0'; // Ensure null-termination
        std::cout << "Received from client: " << buffer << std::endl;

        // You can implement message broadcasting here
        BroadcastMessage(buffer, strlen(buffer), clientSocket);
    }

    close(clientSocket);
    // Remove the client socket from the list
    clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), clientSocket), clientSockets.end());
}


void Server::BroadcastMessage(char* message, int messageLength, int sendClient) {
    //for client in clientsockets send the message to them
    for(int client : clientSockets){
        if (client != sendClient){ //avoids having their message broadcasted back to them
            send(client, message, messageLength, 0);
        }
    }

}