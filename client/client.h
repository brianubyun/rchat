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
    Client();
    ~Client();

    //Client connects to  server
    bool Connect();

    //Client start
    void Start();

    //Send messages while connected
    void SendMessage(const char* message);

    //Disconnects from chat server
    void Disconnect();

protected:
    int clientSocket;
    
private:
    std::string serverDomainName = "xe-01.cs.ucr.edu";// Use domain name instead of IP address
    int serverPort = 48566; //the free port that will be used on the server 

    //Sending messages in a loop
    void SendLoop();

    //Receiving messages in a loop
    void ReceiveLoop();
};

#endif 
