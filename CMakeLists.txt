cmake_minimum_required(VERSION 3.0)
project(RChat)

add_subdirectory(googletest)

add_executable(server_run
            server/main.cpp
            server/server.h
            server/server.cpp
            )

add_executable(client_run
            client/main.cpp
            client/client.h
            client/client.cpp
            )

add_executable(client_test_run
            client/main.cpp
            client/client.h
            client/client.cpp
            server/main.cpp
            server/server.h
            server/server.cpp
            tests/client_shut_off_test.cpp
            )       
            
            
target_link_libraries(client_run PRIVATE pthread)

target_link_libraries(server_run pthread)