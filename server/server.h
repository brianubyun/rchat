#ifndef SERVER_H
#define SERVER_H
#include <vector>
#include <string>


class Server {
public:
    bool isRunning;
    
    Server();

    ~Server();

    //Starts server
    void Start();

    //Stops server
    void Stop();

    //Accepts clients into server
    void AcceptClients();

    //Handles client messaging/messages
    void HandleClient(int clientSocket);

    //Broadcasts message to all connected clients
    void BroadcastMessage(char * message, int messageLength, int sendClient);

    //Authenticates users before sending messages
    void Authenticate(int);
    
private:
    int serverSocket; 
    int port = 48566;
    std::vector<int> clientSockets;
};

#endif 
