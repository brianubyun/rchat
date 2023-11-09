#ifndef USERCRED_H
#define USERCRED_H

#include "user/user.h"
#include <string>
#include <functional>
#include <thread>


class UserCred {
public:
    UserCred();
    ~UserCred();

    void InputCredentials();
    User GetUser();
    
private:
    User credentialUser;
};

#endif 