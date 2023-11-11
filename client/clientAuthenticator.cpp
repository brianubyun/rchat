#include "clientAuthenticator.h"
#include "user/userCred.h"
bool ClientAuthenticator::Register()
{
    return false;
}

void ClientAuthenticator::catchResponse()
{
}

std::string ClientAuthenticator::getLoginString()
{
    std::string loginString;
    loginString += thisUser.getUsername();
    //switched to GetPassword b/c hashPass doesn't exist yet, to be fixed once it does
    loginString += std::to_string(thisUser.GetPassword());
    return loginString;
}

bool ClientAuthenticator::login()
{
    //creates the message to send in the proper format
    std::string loginString = getLoginString();
    char* toSend = new char [loginString.length() + 1]
    for(int i = 0; i < loginString.length(); ++i)
    {
        toSend[i] = loginString.at(i);
    }
    toSend[loginString.length()] = '\0';
    //send username+passhash to server
    //if it exists, return true, else return false
    return false;
}

