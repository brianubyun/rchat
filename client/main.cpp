#include "client.h"
#include <iostream>

int main() {
    Client client;
    
    if (!client.Connect()) {
        std::cerr << "Failed to connect to the server." << std::endl;
        return 1;
    }

    //start client to send and receive messages
    client.Start();
    
    return 0;
}