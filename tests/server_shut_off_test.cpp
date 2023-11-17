#include "../server/server.h"
#include "../client/client.h"
#include "../server/commandhandler.h"
#include <string>
#include <iostream>
#include "gtest/gtest.h" //what is wrong with this 

/*possible solution is to create a public variable that checks if server is deleted*/
/*maybe create test class that overrides handlecommand and addes in a bool to check if deletes*/

//Created a test command handler class with a public bool that is set to true
//When the //exit command has been called, indicating that the server has been stopped and deleted

class TestCommandHandler : public CommandHandler{
    public:
        bool hasBeenDeleted = false;
        void HandleCommand(char* command, Server* server) {
            if(strcmp(command, "//exit") == 0){ //If input is exit command
                std::cin.clear();
                std::cout<<"Shutting down server" << std::endl;
                hasBeenDeleted = true;
                delete server; //call server destructor 
            } 
            else if (command == "command2") {
                std::cout << "Executing Command 2" << std::endl;
                // Add your logic for Command 2
            } else {
                std::cout << "Unknown command: " << command << std::endl;
            }
        }

};


/*
class TestServer: public Server{
    public:
        bool isRunning = false;
        TestServer(){
            std::cout << "Created server" << std::endl;
        }

        ~TestServer(){
            isRunning = false;
        }

        Start(){
            isRunning = true;
        }

}

*/

Server* temp_server;
void RunServer() {
    temp_server = new Server();
    temp_server->Start(); 
    std::this_thread::sleep_for(std::chrono::seconds(10)); // Sleep for 10 seconds
}


TEST(ServerShutDown, testingServerShutOffCommand) {
    Server* server = new Server();
    //server->Start();
    TestCommandHandler commmandhandler;
    std::string input = "//exit";
    char command[input.length() + 1];
    std::strcpy(command, input.c_str());
    commmandhandler.HandleCommand(command, server);
    EXPECT_TRUE(commmandhandler.hasBeenDeleted);
}


int main(int argc, char **argv) {
    //std::thread serverThread(RunServer);
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    //serverThread.join();
    return result;
}