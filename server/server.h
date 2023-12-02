#ifndef SERVER_H
#define SERVER_H
#include <vector>
#include <string>


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
    void AcceptClients();

    // Handle client communication
    void HandleClient(int clientSocket);

    // Broadcast a message to all connected clients
    void BroadcastMessage(char * message, int messageLength, int sendClient);



    //Authenticates users before they are allowed to send messages
    void Authenticate(int);
private:
    int serverSocket; 
    int port = 48566;
    std::vector<int> clientSockets;
    bool threadsRunning;
};

#endif // SERVER_H
