cmake_minimum_required(VERSION 3.0)
project(RChat)

ADD_SUBDIRECTORY(googletest)

add_executable(server_run
            server/main.cpp
            server/server.h
            server/server.cpp
            server/chatlogging.h
            server/commandhandler.h
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


add_executable(baseline_test_run
            tests/baseline_tests.cpp
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
            server/chatlogging.h
            server/commandhandler.h
            )



add_executable(client_shut_off_test
            tests/client_shut_off_test.cpp
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
add_executable(server_shut_off_test
            tests/server_shut_off_test.cpp
            server/server.h
            server/server.cpp
            client/client.h
            client/client.cpp
            server/chatlogging.h
            server/commandhandler.h
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

TARGET_LINK_LIBRARIES(baseline_test_run gtest)
TARGET_COMPILE_DEFINITIONS(baseline_test_run PRIVATE gtest_disable_pthreads=ON)

TARGET_LINK_LIBRARIES(auth_test gtest)
TARGET_COMPILE_DEFINITIONS(baseline_test_run PRIVATE gtest_disable_pthreads=ON)

TARGET_LINK_LIBRARIES(client_shut_off_test gtest)
TARGET_COMPILE_DEFINITIONS(baseline_test_run PRIVATE gtest_disable_pthreads=ON)

TARGET_LINK_LIBRARIES(server_shut_off_test gtest)
TARGET_COMPILE_DEFINITIONS(baseline_test_run PRIVATE gtest_disable_pthreads=ON)