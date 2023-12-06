#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include "server.h"

class CommandHandler {
public:
    void ListenFor(Server* server) {
        char input[10];
        do { //While server is running get input
          std::cin.getline(input, 10);
          HandleCommand(input, server);
          std::cin.clear();
        } while(server->isRunning);
    }

    void HandleCommand(char* command, Server* server) {
         if(strcmp(command, "//exit") == 0) { //If input is exit command
            std::cin.clear();
            std::cout<<"Shutting down server" << std::endl;
            server->SimpleStop(); //call server destructor 
        } 
        else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
};

#endif 