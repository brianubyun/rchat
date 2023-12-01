#ifndef CHATLOGGER_H
#define CHATLOGGER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>


class Logger {
public:
    Logger(std::string saveFileName = "R'ChatLogs.txt") {
        this->saveFile = saveFileName;
    }

    void logMessage(char message[] ) {
        //gets current time
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        //converts time to string
        char timeString[100];  
        std::strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

        //opens file in append mode
        std::ofstream ChatLog(this->saveFile, std::ios_base::app);

        //writes timestamp and msg to file
        ChatLog << "[" << timeString << "] " << message << std::endl;

        ChatLog.close();
    }

private:
    std::string saveFile;
};

#endif 