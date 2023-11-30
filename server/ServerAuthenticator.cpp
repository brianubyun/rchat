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

const bool ServerAuthenticator::isUser(std::string username) {
    //Opens .txt file
    in.open("users.txt");
    if (!in.is_open()) { //Stops if failure to open file
        abort;
    }

    std::string curr;
    while (getline(in, curr)) {
        if (!curr.substr(0, curr.find(breakChar)).compare(username)) { //Username is found when compared to specific format of username stored in file
            in.close(); //Closes file since username is found
            return true;
        }
    }

    //Username not found
    in.close();
    return false;
}

const bool ServerAuthenticator::isUser(char message[]) {
    in.open("users.txt");
    if (!in.is_open()) {
        abort;
    }

    std::string userAndPass(message);
    std::string curr;
    //Puts the string in the right format
    for (int i = 0; i < (userAndPass.length() - 1); ++i) {
        userAndPass.at(i) = userAndPass.at(i+1);
    }
    userAndPass.pop_back();

    while (getline(in, curr)) {
        in.ignore();
        if (!curr.compare(userAndPass)) {
            //in.close();
            return true;
        }
    }
    in.close();
    return false;
}

bool ServerAuthenticator::writeUser(char message[]) {
    out.open("users.txt", std::ios::app);
    if (!out.is_open()) {
        abort;
    }

    std::string userAndPass(message);
    for (int i = 0; i < (userAndPass.length() - 1); ++i) {
        userAndPass.at(i) = userAndPass.at(i+1);
    }
    userAndPass.pop_back();
    userAndPass.append("\n");

    //searches for the username to see if the user already exists
    std::string username = userAndPass.substr(0, userAndPass.find(breakChar));
    if (!isUser(username)) {
        out << userAndPass;
        out.close();
        return true;
    }
    out.close();
    return false;
}

bool ServerAuthenticator::authUser(int clientSocket) {
    char buffer [4096];

    while (true) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            // Handle client disconnection or error
            //break;
            return false;
        }

        buffer[bytesReceived] = '\0'; // Ensure null-termination
        if (buffer[0] == '1') {
            bool isuser = isUser(buffer);
            char message[2];
            if (isuser) {
                message[0] = '1';
            }
            else {
                message[0] = '0';
            }
            message[1] = '\0';

            send(clientSocket, message, 2, 0);
            return isuser;
        }
        else {
            bool writeuser = writeUser(buffer);
            char message [2];
            if (writeuser) {
                message[0] = '1';
            }
            else {
                message[0] = '0';
            }
            message[1] = '\0';

            send(clientSocket, message, 2, 0);
            return writeuser;
        }
    }
    return false;
}
