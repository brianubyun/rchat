#ifndef TESTCLASSES_H
#define TESTCLASSES_H
#include "../server/server.h"
#include "../client/client.h"
#define MAXBYTES 4096
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fstream>
#include <cstdio>


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

#endif 