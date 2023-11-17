#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include <iostream>
#include <string>
#include <cstring>
#include "server.h"

class CommandHandler {
public:
    void ListenFor(Server* server, std::istream& in){
        char* input;
        while(server->isRunning){ //While server is running get input
          in.getline(input, 10);
          HandleCommand(input, server, std::cin, std::cout);
          in.clear();
        }   
    }


    void HandleCommand(char* command, Server* server, std::istream& in, std::ostream& out) {
         if(strcmp(command, "//exit") == 0){ //If input is exit command
            in.clear();
            out<<"Shutting down server" << std::endl;
            delete server; //call server destructor 
        } 
        else if (command == "command2") {
            out << "Executing Command 2" << std::endl;
            // Add your logic for Command 2
        } else {
            out << "Unknown command: " << command << std::endl;
        }
    }
};

#endif 