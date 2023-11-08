#ifndef USER_H
#define USER_H

#include <string>
#include <functional>
#include <thread>


class User {
public:
    User();
    ~user();
    
    //setters
    setUsername();
    setPassword();

    //getters
    getUsername();
    getPassword();

    

protected:
    int clientSocket;
private:
    std::string username;
    std::string password;
};

#endif // CLIENT_H
