cmake_minimum_required(VERSION 3.0)
project(RChat)

ADD_SUBDIRECTORY(googletest)

add_executable(server_run
            server/main.cpp
            server/server.h
            server/server.cpp
            server/chatlogging.h
            server/commandhandler.h
            )

add_executable(client_run
            client/main.cpp
            client/client.h
            client/client.cpp
            )


add_executable(test_run
            tests/tests.cpp
            server/server.h
            server/server.cpp
            client/client.h
            client/client.cpp
            server/chatlogging.h
            server/commandhandler.h
            )

               
target_link_libraries(client_run PRIVATE pthread)
target_link_libraries(server_run pthread)


TARGET_LINK_LIBRARIES(test_run gtest)
TARGET_COMPILE_DEFINITIONS(test_run PRIVATE gtest_disable_pthreads=ON)
