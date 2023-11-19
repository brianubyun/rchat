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


add_executable(baseline_test_run
            tests/baseline_tests.cpp
            server/server.h
            server/server.cpp
            client/client.h
            client/client.cpp
            server/chatlogging.h
            server/commandhandler.h
            )

               
target_link_libraries(client_run PRIVATE pthread)
target_link_libraries(server_run pthread)


TARGET_LINK_LIBRARIES(baseline_test_run gtest)
TARGET_COMPILE_DEFINITIONS(baseline_test_run PRIVATE gtest_disable_pthreads=ON)
