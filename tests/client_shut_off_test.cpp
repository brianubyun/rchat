#include "../googletest/googletest/include/gtest/gtest.h"
#include "../client/client.h"
#include "../server/server.h"

class testClient : public Client {
public: 
    Client testClient;
};

TEST(testClient, quitCommand) {
    std::stringstream userInput("Hello I am Brian.\n I like to eat food. \n//quit")

    testClient.SendLoop();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}