#ifndef USERHANDLING_H
#define USERHANDLING_H

#include <fstream>
#include <string>

class Userhandling
{
    private:
        std::ofstream out;
        std::ifstream in;
        const char breakChar = 17;
        const char nlChar = 10;
    public:
        const bool isUser (std::string username, std::string passhash);
        const bool isUser (std::string username);
        const bool isUser (char*);
        void writeUser (std::string username, std::string passhash);
};
#endif