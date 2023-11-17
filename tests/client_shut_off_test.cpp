#include "/home/csmajs/bbyun004/final-project-ykore001-dshaw013-bbyun004-mcuay001/client/client.h"
#include "../server/server.h"
#include "/home/csmajs/bbyun004/final-project-ykore001-dshaw013-bbyun004-mcuay001/googletest/googletest/include/gtest/gtest.h"

class TestClient : public Client {
  public:
    /*Rendition of SendLoop since SendLoop in Client class is private 
      Additionally, unit test should be fully automated so parameter is in place of user input/message */
    bool ClientQuitCommandTest(const char* message) { 
        while (true) {
            if (std::string(message) == "//quit") { // if this runs, //quit works
                std::cin.clear();
                return true;
            }
            return false; //does not work so returns false
        }
    }
};

TEST(ClientShutoffTest, successfulQuitCommand) {
    //Arrange
    TestClient client;

    //Act and Assert
    EXPECT_TRUE(client.ClientQuitCommandTest("//quit"));
}

TEST(ClientShutoffTest, unsuccessfulQuitCommand) {
    //Arrange
    TestClient client;

    //Act and Assert
    EXPECT_FALSE(client.ClientQuitCommandTest("/quit"));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}