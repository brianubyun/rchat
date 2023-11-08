#include "user.h"
#include "userCred.h"
#include <iostream>

UserCred::UserCred() {}

UserCred::~UserCred() {}

void UserCred::InputCredentials() {
    //logic to take input for use in the prompt method of client authenticator
}

User UserCred::GetUser(){
    return this->credentialUser;
}