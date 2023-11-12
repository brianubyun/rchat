#include "../server/chatlogging.h"
#include "gtest/gtest.h" 
#include <fstream>
#include <cstdio>


// ensures that the logger takes input line by line 
TEST(loggerTest, writeTest) {
    char buffer[] = "Hello world";
    Logger testLog("testLog.txt");

    testLog.logMessage(buffer);


    std::string logText;
    // Read from the text file
    std::ifstream MyReadFile("testLog.txt");

    //getline() function to read the file line by line
    getline (MyReadFile, logText);

    //removes the timestamp of the message
    logText = logText.substr(22);
    
    EXPECT_EQ(buffer, logText);
    MyReadFile.close();
    std::remove("testLog.txt");
}

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    return result;
}