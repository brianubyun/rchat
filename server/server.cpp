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
#include <errno.h>
#include "ServerAuthenticator.h"

using namespace std;
#define MAXBYTES 4096


//initialize a socket for the server 
Server::Server() : isRunning(false){
    
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);//AF_INET ---> Address Family Internet, SOCK_STREAM -- > Stream Socket, 0 is for default so it uses TCP 
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket." << std::endl;
        exit(EXIT_FAILURE);
    }
    int optval = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));
    //Code was adapted from a stackoverflow post: https://stackoverflow.com/a/6326156
    if(fcntl(serverSocket, F_SETFL, fcntl(serverSocket, F_GETFL) | O_NONBLOCK) < 0) {
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

    //create shutoff command thread to check for shut off command
    //this is where we implement the command handler thread instead of the shut off thread
    CommandHandler handler;
    std::thread commandThread;
    commandThread = std::thread(&CommandHandler::ListenFor, &handler, this);
    commandThread.detach(); //detach shut off thread
    AcceptClients();
    isRunning = false;
    Stop();
}

//Stops the server and closes clients 
void Server::Stop() {

    if(isRunning){ return; }
    // Close all client sockets
    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);
    isRunning = false;
    while(clientSockets.size() != 0){}
    //exit here (!e)
    //the threads need to be joined here, if the server exits before they actually complete, it causes a memory leak.
    //the problem from command handler also comes in here: it simply calls the deconstructor to the server.
    exit(0);
}


//Creates threads for each client 
void Server::AcceptClients() {
    std::cout << "listening..." << std::endl;
    bool login = false;
    std::thread clientThread;
    while (isRunning) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

        if (clientSocket == -1) {
            //std::cerr << "Error accepting client connection." << std::endl;
            continue;  // Continue to accept other connections
        }
        //authenticate that they are a user
        if(login)
        {
            login = false;
            std::thread authenticationThread(&Server::Authenticate, this, clientSocket);
            authenticationThread.detach();
        }
        else
        {
            login = true;
            clientSockets.push_back(clientSocket);
            clientThread = std::thread(&Server::HandleClient, this, clientSocket);
            clientThread.detach();
        }
    }
    //clientThread.join();
    std::cout << "\n"; //unsure why this line is needed, but without it theres a memory leak. could not tell you why.
}

//What the thread will do for each client 
void Server::HandleClient(int clientSocket) {
    char buffer[MAXBYTES];
    //clears out the buffer from any messages that may have been sent during the login process
    //ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    Logger chatLog;
    while (isRunning) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            // andle client disconnection or error
            break;
        }
        if (buffer[0] == '0' || buffer[0] == 17)
        {
            break;
        }
        chatLog.logMessage(buffer);

        //Process the received data (in this example, we just print it)
        buffer[bytesReceived] = '\0'; // Ensure null-termination
        std::cout << "Received from " << buffer << std::endl;

        BroadcastMessage(buffer, strlen(buffer), clientSocket);
    }

    close(clientSocket);
    //Removes client from clientSockets
    clientSockets.erase(std::remove(clientSockets.begin(), clientSockets.end(), clientSocket), clientSockets.end());
    std::cout << "\n";
}


void Server::BroadcastMessage(char* message, int messageLength, int sendClient) {
    //for client in clientsockets send the message to them
    for(int client : clientSockets){
        if (client != sendClient){ //avoids having their message broadcasted back to them
            send(client, message, messageLength, 0);
        }
    }

}

void Server::SimpleStop()
{
    char endMsg[2];
    endMsg[0] = (char)18;
    endMsg[1] = '\0';
    BroadcastMessage(endMsg, 2, 0);
    isRunning = false;
}

void Server::Authenticate(int clientSocket)
{
    //Fixed: failed login closes connection to client-side 
    ServerAuthenticator auth;
    bool authenticated = auth.authUser(clientSocket);
    if(!authenticated)
    {
        return;
    }
    close(clientSocket);
}