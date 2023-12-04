#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include "server.h"

class CommandHandler {
public:
    void ListenFor(Server* server){
        char* input;
        while(server->isRunning){ //While server is running get input
          std::cin.getline(input, 10);
          HandleCommand(input, server);
          std::cin.clear();
        }   
    }


    void HandleCommand(char* command, Server* server) {
         if(strcmp(command, "//exit") == 0){ //If input is exit command
            std::cin.clear();
            std::cout<<"Shutting down server" << std::endl;
            //this is not the best way to go about this. itd be better to set a flag or smt on the server to tell the server its time to exit, and allow it to do so gracefully.
            server->SimpleStop(); //call server destructor 
        } 
        else if (command == "command2") {
            std::cout << "Executing Command 2" << std::endl;
            // Add your logic for Command 2
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
};

#endif 