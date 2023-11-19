#include "../server/server.h"
#include "../client/client.h"
#include "gtest/gtest.h" //what is wrong with this 


#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MAXBYTES 4096



class TestServer : public Server {
public:
    void TestStop (){
        exit(0);
    }
};

class TestClient : public Client {
public:
    void TestSend() {
      int i = 1;
      while (i >= 0) {
        char testBuffer[] = "Hello, World!";
        SendMessage(testBuffer);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        i--;
      }
    }


    bool TestReceive() {
      char buffer[MAXBYTES];
      while (true) {
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            return true;
        }
        else {
            return false;
        }
        
      }
    }
};

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


TEST(BroadcastTest, Message) {
    TestClient listenClient;
    listenClient.Connect();
    EXPECT_TRUE(listenClient.TestReceive());
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
