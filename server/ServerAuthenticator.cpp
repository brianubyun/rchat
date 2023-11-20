#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <algorithm>
#include "ServerAuthenticator.h"
//#define MAXBYTES 4096
using namespace std;
const bool ServerAuthenticator::isUser(std::string username, std::string passhash)
{
    ifstream in;
    in.open("users.txt");
    if(!in.is_open())
    {
        abort;
    }
    stringstream uAndP;
    string userAndPass;
    uAndP << username << breakChar << passhash;
    uAndP >> userAndPass;
    string curr;
    while(getline(in, curr))
    {
        if(!curr.compare(userAndPass))
        {
            return true;
        }
    }
    in.close();
    return false;
}

const bool ServerAuthenticator::isUser(std::string username)
{
    in.open("users.txt");
    if(!in.is_open())
    {
        abort;
    }
    string curr;
    while(getline(in, curr))
    {
        std::cout << curr.substr(0, curr.find(breakChar)).compare(username) << std::endl;
        if(!curr.substr(0, curr.find(breakChar)).compare(username))
        {
            return true;
        }
    }
    in.close();
    return false;
}

const bool ServerAuthenticator::isUser(char message[])
{
    cout << "CHECKING USER\n";
    in.open("users.txt");
    if(!in.is_open())
    {
        abort;
    }
    string userAndPass(message);
    cout << "RAW USER STRING: " << userAndPass << endl;
    string curr;
    //puts the string in the right format
    for(int i = 0; i < (userAndPass.length() - 1); ++i)
    {
        userAndPass.at(i) = userAndPass.at(i+1);
    }
    userAndPass.pop_back();
    cout << "FIXED USER STRING: " << userAndPass << endl;
    while(getline(in, curr))
    {
        in.ignore();
        std::cout << "CURRENT STRING: " << curr << endl;
        if(!curr.compare(userAndPass))
        {
            cout << "MATCHES USER STRING\n";
            return true;
        }
        cout << "DOESN'T MATCH USER STRING\n";
    }
    return false;
}

bool ServerAuthenticator::writeUser(char message[])
{
    cout << "WRITING USER\n";
    out.open("users.txt", ios::app);
    if(!out.is_open())
    {
        abort;
    }
    string userAndPass(message);
    cout << "RAW USER STRING: " << userAndPass << endl;
    for(int i = 0; i < (userAndPass.length() - 1); ++i)
    {
        userAndPass.at(i) = userAndPass.at(i+1);
    }
    userAndPass.pop_back();
    userAndPass.append("\n");
    cout << "FIXED USER STRING: " << userAndPass << endl;
    //searches for the username to see if the user already exists
    cout << "USERNAME: " << userAndPass.substr(0, userAndPass.find(breakChar)) << endl;
    string username = userAndPass.substr(0, userAndPass.find(breakChar));
    if(!isUser(username))
    {
        cout << "USER NOT FOUND, REGISTERING\n";
        out << userAndPass;
        out.close();
        return true;
    }
    out.close();
    cout << "USER FOUND\n";
    return false;
}

bool ServerAuthenticator::authUser(int clientSocket)
{
    cout << "AUTHENTICATING USER\n";
    char buffer [4096];
    while (true) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            // Handle client disconnection or error
            //break;
        }
        buffer[bytesReceived] = '\0'; // Ensure null-termination
        std::cout << buffer << endl;
        if(buffer[0] == '1')
        {
            cout << "LOGIN\n";
            bool isuser = isUser(buffer);
            char message [2];
            if(isuser){message[0] = '1';cout << "1\n";}
            else{message[0] = '0';cout << "0\n";}
            message[1] = '\0';
            send(clientSocket, message, 2, 0);
            return isuser;
        }
        else
        {
            cout << "REGISTERING\n";
            bool writeuser = writeUser(buffer);
            char message [2];
            if(writeuser){message[0] = '1';cout << "SUCCESS\n";}
            else{message[0] = '0';cout << "FAILURE\n";}
            message[1] = '\0';
            send(clientSocket, message, 2, 0);
            return writeuser;
        }
    }
    return false;
}
