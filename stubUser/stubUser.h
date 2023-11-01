#ifndef STUBUSER_H
#define STUBUSER_H

#include <string>

class stubUser {
public:

    // Constructor
    stubUser();

    //Destructor
    ~stubUser();

    // Returns username
    std::string getUsername() const;

    //Returns password
    std::string getPassword() const; 

    // Allows user to register
    bool Register();

    // Allows user to login
    void Login();
protected:
    std::string username, password;
};

#endif