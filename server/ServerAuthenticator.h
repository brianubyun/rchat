#ifndef SERVERAUTHENTICATOR_H
#define SERVERAUTHENTICATOR_H

#include <fstream>
#include <string>

class ServerAuthenticator
{
    private:
        std::ofstream out;
        std::ifstream in;
        const char breakChar = 17;
        const char nlChar = 10;
    public:
        const bool isUser (std::string username, std::string passhash);
        const bool isUser (std::string username);
        const bool isUser (char[4096]);
        bool writeUser (char[4096]);
        bool authUser (int);
};
#endif