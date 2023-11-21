#include "../server/server.h"
#include "../client/client.h"
#include "../server/chatlogging.h"
#include "testClasses.h"
#include "gtest/gtest.h" //what is wrong with this 

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fstream>
#include <cstdio>
#define MAXBYTES 4096




//runs server so that infinite listen loop doesnt prevent the connectioin test
void RunServer(TestServer server) {
    server.Start();
}

void KillServer(TestServer server) {
    server.TestStop();
}

//function to be fed into thread and send constant stream of messages to server
void RunSendClient() {
    TestClient sendClient;
    sendClient.Connect();
    sendClient.TestSend();
}




TEST(ConnectionTest, Connect) {
    Client client;
    EXPECT_TRUE(client.Connect());
}


TEST(BroadcastTest, Message) {
    TestClient listenClient;
    listenClient.Connect();
    EXPECT_TRUE(listenClient.TestReceive());
}

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
    TestServer server;
    std::thread serverThread(std::bind(RunServer, server));
    std::thread sendClientThread(RunSendClient);
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    std::thread shutoffThread(std::bind(KillServer, server));
    shutoffThread.join();

    return result;
}

