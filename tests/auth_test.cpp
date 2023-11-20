#include "../server/server.h"
#include "../client/client.h"
#include "../server/ServerAuthenticator.h"
#include "../client/assist/clientAuth.h"
#include "../client/user/user.h"
#include "../client/user/userCred.h"

#include "gtest/gtest.h"  


#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sstream>
#include <fstream>
using namespace std;
TEST(userTests, username/password)
{
    User user();
    user.SetUsername("test");
    user.SetPassword("test");
    ASSERT_TRUE(user.GetUsername().compare("test"));
    ASSErt_TRUE(user.GetPassword().compare("-841574"));
}
TEST(userTests, getCred)
{
    UserCred usercred;
    istringstream in("test\ntest");
    ostringstream out;
    usercred.InputCredentials(in, out);
    User user;
    user = usercred.GetUser();
    ASSERT_TRUE(user.GetUsername().compare("test"));
    ASSERt_TRUE(user.GetPassword().compare("-841574"));
}
TEST(serverAuthTests, isUserUsernameOnlyTrue)
{
    ofstream out("users.txt");
    out << "test4700203200\n";
    ServerAuthenticator auth;
    ASSERT_TRUE(auth.isUser(to_string("test")));
}
TEST(serverAuthTests, isUserUsernameOnlyFalse)
{
    ofstream out("users.txt");
    out << "test4700203200\n";
    ServerAuthenticator auth;
    ASSERT_TRUE(!auth.isUser(to_string("fake")));
}
TEST(serverAuthTests, isUserUsernameAndPasswordTrue)
{
    ofstream out("users.txt");
    out << "test4700203200\n";
    ServerAuthenticator auth;
    ASSERT_TRUE(auth.isUser("test4700203200\n"));
}
TEST(serverAuthTests, isUserUsernameAndPasswordFalse)
{
    ofstream out("users.txt");
    out << "test4700203200\n";
    ServerAuthenticator auth;
    ASSERT_TRUE(auth.isUser("test4700202200\n"));
}
TEST(serverAuthTests, writeUser)
{
    ServerAuthenticator auth;
    auth.writeUser("test\n");
    ASSERT_TRUE(auth.isUser("test\n"));
}
