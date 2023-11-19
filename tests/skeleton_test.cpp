#include "../server/server.h"
#include "../client/client.h"
#include "gtest/gtest.h" //what is wrong with this 

class TestServer : public Server {
public:
    void TestStop (){
        exit(0);
    }
};

//runs server so that infinite listen loop doesnt prevent the connectioin test
void RunServer(TestServer server) {
    server.Start();
}

void KillServer(TestServer server) {
    server.TestStop();
}

TEST(ConnectionTest, Connect) {
    Client client;
    EXPECT_TRUE(client.Connect());
}

int main(int argc, char **argv) {
    TestServer server;
    std::thread serverThread(std::bind(RunServer, server));
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    std::thread shutoffThread(std::bind(KillServer, server));
    shutoffThread.join();
    return result;

    
}



 


