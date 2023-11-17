#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <functional>
#include <thread>
#include <iostream>

class Client {
public:
    Client();
    Client(Client& client){};
    ~Client();

    // Connect to the server
    bool Connect();

    // Start the client
    void Start();

    // Send a message to the server
    void SendMessage(const char* message);

    // Disconnect from the server
    void Disconnect();

    // Function for sending messages in a loop
    void SendLoop(std::istream& in);

    // Function for receiving messages in a loop
    void ReceiveLoop(std::ostream& out);

protected:
    int clientSocket;
private:
    std::string serverDomainName = "xe-01.cs.ucr.edu";// Use domain name instead of IP address
    int serverPort = 48566; //the free port that will be used on the server 
    std::thread sendThread;
    std::thread receiveThread;

    
};

#endif // CLIENT_H
