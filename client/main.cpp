#include "client.h"
#include <iostream>

int main() {
    // Create a client instance
    Client client;
    
    // Connect to the server
    if (!client.Connect()) {
        std::cerr << "Failed to connect to the server." << std::endl;
        return 1;
    }

    // Start the client (send and receive messages)
    client.Start();
    
    return 0;
}