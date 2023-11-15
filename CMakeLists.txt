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


add_executable(skeleton_test
            tests/skeleton_test.cpp
            server/server.h
            server/server.cpp
            client/client.h
            client/client.cpp
            server/chatlogging.h
            server/commandhandler.h
            )


add_executable(broadcast_test
            tests/broadcast_test.cpp
            server/server.h
            server/server.cpp
            client/client.h
            client/client.cpp
            server/chatlogging.h
            server/commandhandler.h
            )

            
add_executable(chatlogging_test
            tests/chatlogging_test.cpp
            server/chatlogging.h
            )

add_executable(server_shut_off_test
            tests/server_shut_off_test.cpp
            server/server.h
            server/server.cpp
            client/client.h
            client/client.cpp
            server/chatlogging.h
            server/commandhandler.h
            )

            
add_executable(chatlogging_test
            tests/chatlogging_test.cpp
            server/chatlogging.h
            )

add_executable(server_shut_off_test
            tests/server_shut_off_test.cpp
            server/server.h
            server/server.cpp
            client/client.h
            client/client.cpp
            )

               
target_link_libraries(client_run PRIVATE pthread)
target_link_libraries(server_run pthread)


TARGET_LINK_LIBRARIES(skeleton_test gtest)
TARGET_COMPILE_DEFINITIONS(skeleton_test PRIVATE gtest_disable_pthreads=ON)

TARGET_LINK_LIBRARIES(broadcast_test gtest)
TARGET_COMPILE_DEFINITIONS(broadcast_test PRIVATE gtest_disable_pthreads=ON)

TARGET_LINK_LIBRARIES(chatlogging_test gtest)
TARGET_COMPILE_DEFINITIONS(skeleton_test PRIVATE gtest_disable_pthreads=ON)

TARGET_LINK_LIBRARIES(server_shut_off_test gtest)
TARGET_COMPILE_DEFINITIONS(server_shut_off_test  PRIVATE gtest_disable_pthreads=ON)