#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>

class Server {
public:
    bool isRunning;
    
    Server();

    ~Server();

    void Start();

    void Stop();

    void AcceptClients();

    void HandleClient(int clientSocket);

    void BroadcastMessage(char * message, int messageLength, int sendClient);

    void SimpleStop();

    void Authenticate(int);
private:
    int serverSocket; 
    int port = 48566;
    std::vector<int> clientSockets;
};

#endif 
