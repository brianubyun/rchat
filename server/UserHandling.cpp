#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "UserHandling.h"
using namespace std;
const bool Userhandling::isUser(std::string username, std::string passhash)
{
    ifstream in;
    in.open("users.txt");
    if(!in.is_open())
    {
        abort;
    }
    stringstream userAndPass;
    string uAndP;
    userAndPass << username << breakChar << passhash;
    userAndPass >> uAndP;
    string curr;
    while(getline(in, curr))
    {
        if(!curr.compare(uAndP))
        {
            return true;
        }
    }
    in.close();
    return false;
}

bool Userhandling::isUser(std::string username)
{
    in.open("users.txt");
    if(!in.is_open())
    {
        abort;
    }
    string curr;
    while(getline(in, curr))
    {
        if(!curr.substr(0, curr.find(breakChar)).compare(username))
        {
            return true;
        }
    }
    in.close();
    return false;
}

void Userhandling::writeUser(std::string username, std::string passhash)
{
    out.open("users.txt", ios::app);
    if(!out.is_open())
    {
        abort;
    }
    out << username << breakChar << passhash << nlChar;
    out.close();
}