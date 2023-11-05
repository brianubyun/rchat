#include "stubUser.h"
#include <iostream>
#include <string>

int main() {
    stubUser stubUser;

    bool isRegistered = stubUser.Register();
    if (isRegistered) {
        std::cout << "Registered." << std::endl;
    }
    else {
        std::cout << "Failed to register." << std::endl;
    }

    return EXIT_SUCCESS;
}