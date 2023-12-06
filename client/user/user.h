#ifndef USER_H
#define USER_H

#include <string>
#include <functional>
#include <thread>
#include <cmath>


class User {
public:
    User();
    ~User();
    
    //setters
    void SetUsername(std::string username);
    void SetPassword(std::string password);

    //getters
    std::string GetUsername();
    std::string GetPassword();

private:
    std::string username;
    std::string password;
};

#endif 
