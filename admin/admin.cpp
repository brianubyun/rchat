#include "admin.h"
#include <iostream>
#include <string>

std::string Admin::getLogs() {
    std::cout << "Get logs" << std::endl;
}

void Admin::shutDownServer() {
    std::cout << "Shut down server." << std::endl;
}

std::string Admin::filterLogs() {
    std::cout << "Filter logs." << std::endl;
}

bool Admin::removeUser(std::string username) {
    return true;
}

bool Admin::muteUser(std::string username, int time) {
    return true;
}