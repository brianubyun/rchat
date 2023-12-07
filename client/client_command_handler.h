#ifndef CLIENTCOMMANDHANDLER_H
#define CLIENTCOMMANDHANDLER_H

#include <iostream>
#include <string>
#include <cstring>

#include "client.h"
#include "emojis.h"

class ClientCommandHandler {
public:
    std::string HandleCommand(std::string& message) {
      //Process the emoji(s) (if any)
      std::string processedMesssage = Emoji::ProcessMessage(message);
      return processedMesssage;
    }
};

#endif 