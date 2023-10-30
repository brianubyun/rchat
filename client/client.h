#ifndef CLIENT_H
#define CLIENT_H

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


private:
    int clientSocket;
    std::string serverDomainName = "xe-01.cs.ucr.edu";// Use domain name instead of IP address
    int serverPort = 48566; //the free port that will be used on the server 
    std::thread sendThread;
    std::thread receiveThread;

    // Function for sending messages in a loop
    void SendLoop();

    // Function for receiving messages in a loop
    void ReceiveLoop();

    void ListCommands(char*);
};

#endif // CLIENT_H
