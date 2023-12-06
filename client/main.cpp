#include "client.h"
#include <iostream>

int main() {
    Client client;

    if (!client.Connect()) {
        std::cerr << "Failed to connect to the server." << std::endl;
        return 1;
    }

    client.Start(); 
    return 0;
}