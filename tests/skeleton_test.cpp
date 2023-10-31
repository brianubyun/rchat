#include "../server/server.h"
#include "../client/client.h"
#include "gtest/gtest.h" //what is wrong with this 

//runs server so that infinite listen loop doesnt prevent the connectioin test
void RunServer() {
    Server server;
    server.Start(); 
    std::this_thread::sleep_for(std::chrono::seconds(10)); // Sleep for 10 seconds
}

TEST(ConnectionTest, Connect) {
    Client client;
    EXPECT_TRUE(client.Connect());
}

int main(int argc, char **argv) {

    std::thread serverThread(RunServer);
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    serverThread.join();

    return result;
}






