#ifndef SERVER_H
#define SERVER_H
#include <vector>
#include <string>


class Server {
public:
    // Constructor
    Server();

    // Destructor
    ~Server();

    // Start the server
    void Start();

    // Stop the server
    void Stop();

    // Accept client connections
    void AcceptClients();

    // Handle client communication
    void HandleClient(int clientSocket);

    // Broadcast a message to all connected clients
    void BroadcastMessage(char message);

private:
    int serverSocket; 
    int port = 48566;
    bool isRunning;
    std::vector<int> clientSockets;

};

#endif // SERVER_H
