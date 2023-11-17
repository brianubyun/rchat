#ifndef SERVER_H
#define SERVER_H
#include <vector>
#include <string>
#include <iostream>


class Server {
public:
    bool isRunning;
    
    // Constructor
    Server();

    // Destructor
    ~Server();

    // Start the server
    void Start();

    // Stop the server
    void Stop();

    // Accept client connections
    void AcceptClients(std::ostream& out);

    // Handle client communication
    void HandleClient(int clientSocket, std::ostream& out);

    // Broadcast a message to all connected clients
    void BroadcastMessage(char * message, int messageLength, int sendClient);



private:
    int serverSocket; 
    int port = 48566;
    std::vector<int> clientSockets;

};

#endif // SERVER_H
