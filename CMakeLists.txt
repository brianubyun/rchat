cmake_minimum_required(VERSION 3.0)
project(RChat)

ADD_SUBDIRECTORY(googletest)

add_executable(server_run
            server/main.cpp
            server/server.h
            server/server.cpp
            server/ServerAuthenticator.h
            server/ServerAuthenticator.cpp
            )

add_executable(client_run
            client/main.cpp
            client/client.h
            client/client.cpp

            client/user/user.h
            client/user/user.cpp

            client/user/userCred.h
            client/user/userCred.cpp
            client/assist/clientAuth.h
            client/assist/clientAuth.cpp

            )


add_executable(skeleton_test
            tests/skeleton_test.cpp
            server/server.h
            server/server.cpp
            
            client/client.h
            client/client.cpp

            client/user/user.h
            client/user/user.cpp

            client/user/userCred.h
            client/user/userCred.cpp
            client/assist/clientAuth.h
            client/assist/clientAuth.cpp
            server/ServerAuthenticator.h
            server/ServerAuthenticator.cpp
            )

add_executable(broadcast_test
            tests/broadcast_test.cpp
            server/server.h
            server/server.cpp
            
            client/client.h
            client/client.cpp

            client/user/user.h
            client/user/user.cpp

            client/user/userCred.h
            client/user/userCred.cpp
            client/assist/clientAuth.h
            client/assist/clientAuth.cpp
            server/ServerAuthenticator.h
            server/ServerAuthenticator.cpp
            )        
add_executable(auth_test
            tests/auth_test.cpp
            server/server.h
            server/server.cpp
            
            client/client.h
            client/client.cpp

            client/user/user.h
            client/user/user.cpp

            client/user/userCred.h
            client/user/userCred.cpp
            client/assist/clientAuth.h
            client/assist/clientAuth.cpp
            server/ServerAuthenticator.h
            server/ServerAuthenticator.cpp
            )
               
target_link_libraries(client_run PRIVATE pthread)
target_link_libraries(server_run pthread)


TARGET_LINK_LIBRARIES(skeleton_test gtest)
TARGET_COMPILE_DEFINITIONS(skeleton_test PRIVATE gtest_disable_pthreads=ON)

TARGET_LINK_LIBRARIES(broadcast_test gtest)
TARGET_COMPILE_DEFINITIONS(broadcast_test PRIVATE gtest_disable_pthreads=ON)