#ifndef CLIENTAUTH_H
#define CLIENTAUTH_H

#include "../user/user.h"
#include "userCred.h"

#include <string>
#include <functional>
#include <thread>


class ClientAuth {
public:
    ClientAuth();
    ~ClientAuth();

    void Prompt();
    bool Register();
    bool Login();
    bool ServerResponse();
    User GetUser();
    
private:
    User authenticationUser;
};

#endif 