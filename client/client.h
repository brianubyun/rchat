#ifndef CLIENT_H
#define CLIENT_H

#include "user/user.h"
#include "user/userCred.h"
#include "assist/clientAuth.h"

#include <string>
#include <functional>
#include <thread>


class Client {
public:
    bool isRunning;
    Client();
    ~Client();

    bool Connect();

    void Start();

    void SendMessage(const char* message);

    void Disconnect();

protected:
    int clientSocket;
    
private:
    std::string serverDomainName = "xe-01.cs.ucr.edu";// Use domain name instead of IP address
    int serverPort = 48566; //Free port that will be used on the server 

    //Function for sending messages in a loop
    void SendLoop(std::string username);

    //Function for receiving messages in a loop
    void ReceiveLoop();
    bool firstMessage;
    bool killThreads;
};

#endif
