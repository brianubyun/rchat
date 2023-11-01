#ifndef ADMIN_H
#define ADMIN_H

#include "../stubUser/stubUser.h"
#include <string>

class Admin : public stubUser {
public:

    // Removes a user from the chat system
    bool removeUser(std::string );

    // Get chat logs 
    std::string getLogs();

    // Shuts down entire server that hosts chat system
    void shutDownServer();

    // Search through logs to find something
    std::string filterLogs();

    // Temporarily mutes a user for certain amount of time
    bool muteUser(std::string, int); 

private: 
    std::string username, password;
};

#endif