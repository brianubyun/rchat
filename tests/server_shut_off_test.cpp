#include "../server/server.h"
#include "../client/client.h"
#include "gtest/gtest.h" //what is wrong with this 

#include <iostream>

class TestServer : public Server {
public:
    bool TestShutOffCommand(){
        //char* input;
        std::cout<<"Called" << std::endl;
        while(isRunning){ //While server is running get input
            //cin.getline("//exit", 10);
            if(strcmp("//exit", "//exit") == 0){ //If input is exit command
                //cin.clear();
                std::cout<<"Shutting down server" << std::endl;
                return true;
                //delete this; //call server destructor 
            } 
        }
        return false;     
    }

};


void RunServer() {
    Server server;
    server.Start(); 
    std::this_thread::sleep_for(std::chrono::seconds(10)); // Sleep for 10 seconds
}


TEST(ServerShutDown, testingServerShutOffCommand) {
    TestServer server;
    server.Start(); 
    std::this_thread::sleep_for(std::chrono::seconds(10)); // Sleep for 10 seconds
    EXPECT_TRUE(server.TestShutOffCommand());
}


int main(int argc, char **argv) {
    //std::thread serverThread(RunServer);
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    //serverThread.join();

    return result;
}