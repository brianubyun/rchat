#ifndef USERCRED_H
#define USERCRED_H

#include "user.h"

#include <string>
#include <functional>
#include <thread>

class UserCred {
public:
    UserCred();
    ~UserCred();

    void InputCredentials(std::ostream &out, std::istream &in);
    User GetUser();
    
private:
    User credentialUser;
};

#endif 