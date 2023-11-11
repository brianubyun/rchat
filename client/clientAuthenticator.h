#ifndef CLIENTAUTHENTICATOR_H
#define CLIENTAUTHENTICATOR_H
#include "../user/user.h"
#include <string>
class ClientAuthenticator 
{
    private:
        User thisUser;
    public:
        bool Register();
        bool Login();
        void catchResponse();
        std::string getLoginString();
};
#endif