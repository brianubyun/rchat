#ifndef CLIENT_H
#define CLIENT_H

#include "user/user.h"
#include "userCred.h"
#include "clientAuth.h"

#include <string>
#include <functional>
#include <thread>


class Client {
public:
    Client();
    ~Client();

    // Connect to the server
    bool Connect();

    // Start the client
    void Start();

    // Send a message to the server
    void SendMessage(const char* message);

    // Disconnect from the server
    void Disconnect();

protected:
    int clientSocket;
private:
    std::string serverDomainName = "xe-01.cs.ucr.edu";// Use domain name instead of IP address
    int serverPort = 48566; //the free port that will be used on the server 

    // Function for sending messages in a loop
    void SendLoop();

    // Function for receiving messages in a loop
    void ReceiveLoop();
};

#endif // CLIENT_H
