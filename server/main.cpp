#include "server.h"
#include <iostream> 
int main() {
    Server server;
    server.Start();
    std::cout << "Server exited successfully.\n";
    return 0;
}