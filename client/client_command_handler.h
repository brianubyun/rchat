#ifndef CLIENTCOMMANDHANDLER_H
#define CLIENTCOMMANDHANDLER_H
#include <iostream>
#include <string>
#include <cstring>
#include "client.h"
#include "emojis.h"

class ClientCommandHandler {
public:
     bool HandleCommand(char* message, Client* client) {
         if (strcmp(message, "//exit") == 0) { //If input is exit command
            std::cin.clear();
            std::cout<< "Shutting down client" << std::endl;
            return false;
          }
          else { // process the emoji(s) (if any)
            std::string processedMesssage;
            processedMesssage = Emoji::ProcessMessage(message);
            client->SendMessage(processedMesssage);
            return true;
          }
     }
};

#endif 