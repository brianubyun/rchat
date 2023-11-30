#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <iostream>
#include <string>
#include <cstring>

#include "server.h"

class CommandHandler {
public:
    void ListenFor(Server* server) {
        char* input;
        while(server->isRunning) { //While server is running, get input
            std::cin.getline(input, 10);
            HandleCommand(input, server);
            std::cin.clear();
        }   
    }


    void HandleCommand(char* command, Server* server) {
        if(strcmp(command, "//exit") == 0){ //If input is exit command
            std::cin.clear();
            std::cout<<"Shutting down server" << std::endl;
            delete server; //call server destructor 
        } 
        else if (command == "command2") { //Here if we want to implement any other commands
            std::cout << "Executing Command 2" << std::endl;
        } 
        else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
};

#endif 