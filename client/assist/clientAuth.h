#ifndef CLIENTAUTH_H
#define CLIENTAUTH_H

#include "../user/user.h"
#include "../user/userCred.h"

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <functional>
#include <thread>


class ClientAuth {
public:
    ClientAuth(int clientSocket, int serverport, std::string serverDomainName);
    ~ClientAuth();

    void Prompt();
    bool Register();
    bool Login();
    bool ServerResponse();
    User GetUser();
    
private:
    User authenticationUser;
    int authSocket;
    int serverPort;
    std::string serverDomainName;
    std::string loginString();
};

#endif 