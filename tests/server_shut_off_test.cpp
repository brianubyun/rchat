#include "../server/server.h"
#include "../client/client.h"
#include "../server/commandhandler.h"
#include <string>
#include <iostream>
#include "gtest/gtest.h" //what is wrong with this 


//Global server object that is required for unit test
Server* temp_server;

//Function to run the server and pause threads for 1 second
void RunServer() {
    temp_server = new Server();
    temp_server->Start(); 
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

//Function to run command handler and get exit input then shutdown the sever
void RunCommandHandler(){
    CommandHandler commmandhandler;
    std::string input = "//exit";
    char command[input.length() + 1];
    std::strcpy(command, input.c_str());
    std::this_thread::sleep_for(std::chrono::seconds(2));
    commmandhandler.HandleCommand(command, temp_server);
}

//Function to test for expected exit
void NormalExit(){
    std::thread serverThread(RunServer);
    std::thread commmandThread(RunCommandHandler);
    serverThread.join();
    commmandThread.join();
}

TEST(ServerShutDown, testingServerShutOffCommand) {
   EXPECT_EXIT(NormalExit(),testing::ExitedWithCode(0),"");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}