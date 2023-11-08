#include "user.h"
#include "userCred.h"
#include "clientAuth.h"
#include <iostream>

ClientAuth::ClientAuth() {}

ClientAuth::~ClientAuth() {}

void ClientAuth::Prompt() {
    //logic to take input for use in the prompt method of client authenticator
}

bool ClientAuth::Register() {
    //logic to take input for use in the prompt method of client authenticator
}

bool ClientAuth::Login() {
    //logic to take input for use in the prompt method of client authenticator
}

bool ClientAuth::ServerResponse() {
    //logic to take input for use in the prompt method of client authenticator
}


User ClientAuth::GetUser(){
    return this->credentialUser;
}