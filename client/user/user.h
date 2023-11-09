#ifndef USER_H
#define USER_H

#include <string>
#include <functional>
#include <thread>


class User {
public:
    User();
    ~User();
    
    //setters
    void SetUsername();
    void SetPassword();

    //getters
    string GetUsername();
    string GetPassword();

private:
    std::string username;
    std::string password;
};

#endif // USER_H
