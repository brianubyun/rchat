#ifndef CLIENTCOMMANDHANDLER_H
#define CLIENTCOMMANDHANDLER_H
#include <iostream>
#include <string>
#include <cstring>
#include "client.h"
#include "emojis.h"

class ClientCommandHandler {
public:
     static bool HandleCommand(const std::string& message, Client* client) {
         if (message == "//exit") { //If input is exit command
            std::cin.clear();
            std::cout<< "Shutting down client" << std::endl;
            return false;
          }
          else { // process the emoji(s) (if any)
            std::string processedMesssage;
            processedMesssage = Emoji::ProcessMessage(message);
            client->SendMessage(processedMesssage.c_str());
            return true;
          }
     }
};

#endif 