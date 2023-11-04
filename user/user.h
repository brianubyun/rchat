#ifndef USER_H
#define USER_H
#include <string>
#include "../client/client.h"
class User : private Client
{
    private:
        std::string username;
        std::string password;
        const int breakChar = 17;
    public:
        User(std::string user, std::string pass) : username(user), password(pass) {};
        int hashPass(std::string);
        bool login ();
        bool signUp();
        std::string getUsername();
        void setUsername(std::string);
        void setPass(std::string);
};
#endif