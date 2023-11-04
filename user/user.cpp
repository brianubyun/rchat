#include "../client/client.h"
#include "user.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MAXBYTES 4096
int User::hashPass(std::string pass)
{
    return pass.length();
}

bool User::login()
{
    std::string hash;
    hash = std::to_string(hashPass(password));
    new char [hash.length() + username.length() + 2] toSend;
    for(int i = 0; i < username.length(); ++i)
    {
        toSend[i] = username.at(i);
    }
    toSend[username.length()] = breakChar;
    for (int i = 0; i < hash.length; ++i)
    {
        toSend[username.length() + i + 1] = hash.at(i);
    }
    toSend[hash.length() + username.length() + 1] = '\0';
    //send username+passhash to server
    //if it exists, return true, else return false
    return false;
}
