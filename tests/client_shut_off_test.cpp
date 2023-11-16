#include "../client/client.h"
#include "../server/server.h"
#include "/home/csmajs/bbyun004/final-project-ykore001-dshaw013-bbyun004-mcuay001/googletest/googletest/include/gtest/gtest.h"

class testClient : public Client {
public: 
    Client testClient;
};

TEST(testClient, quitCommand) {
    std::stringstream userInput("Hello I am Brian.\n Welcome. \n//quit")

    testClient.SendLoop();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}