#ifndef CHATLOGGER_H
#define CHATLOGGER_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


class Logger {
public:
    
    void logMessage(char message[] ){

      // Get the current time
      auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

      // Convert the current time to a string
      char timeString[100];  // Adjust the size based on your needs
      std::strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

      // Open the file in append mode
      std::ofstream ChatLog("filename.txt", std::ios_base::app);

      // Write the timestamp and message to the file
      ChatLog << "[" << timeString << "] " << message << std::endl;
      
      ChatLog.close();
    }

};

#endif // SERVER_H