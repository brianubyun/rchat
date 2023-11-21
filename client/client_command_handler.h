#ifndef CLIENTCOMMANDHANDLER_H
#define CLIENTCOMMANDHANDLER_H
#include <iostream>
#include <string>
#include <cstring>
#include "client.h"
#include "emojis.h"

class ClientCommandHandler {
public:
    void ListenFor(Client* client){
        char* input;
        while(client->isRunning){ //While client is running get input
          std::cin.getline(input, 10);
          HandleCommand(input, client);
          std::cin.clear();
        }   
    }

     void HandleCommand(char* command, Client* server) {
         if(strcmp(command, "//exit") == 0) { //If input is exit command
            std::cin.clear();
            std::cout<<"Shutting down client" << std::endl;
            delete Client; //call client destructor 
     }
};

#endif 