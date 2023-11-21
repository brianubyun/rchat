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
TEST(userTests, usernamePassword)
{
    User user;
    user.SetUsername("test");
    user.SetPassword("test");
    ASSERT_TRUE(!user.GetUsername().compare("test"));
    ASSERT_TRUE(!user.GetPassword().compare("4700203200"));
}
TEST(userTests, getCred)
{
    UserCred usercred;
    istringstream in("test\ntest");
    ostringstream out;
    usercred.InputCredentials(out, in);
    User user;
    user = usercred.GetUser();
    ASSERT_TRUE(!user.GetUsername().compare("test"));
    ASSERT_TRUE(!user.GetPassword().compare("4700203200"));
}

TEST(serverAuthTests, isUserUsernameOnlyTrue)
{
    ofstream out("users.txt");
    out << "test4700203200\n";
    out.close();
    ServerAuthenticator auth;
    string str("test");
    ASSERT_TRUE(auth.isUser(str));
}
TEST(serverAuthTests, isUserUsernameOnlyFalse)
{
    ofstream out("users.txt");
    out << "test4700203200\n";
    out.close();
    ServerAuthenticator auth;
    string str("fake");
    ASSERT_TRUE(!(auth.isUser(str)));
}
TEST(serverAuthTests, signUp)
{
    ofstream out("users.txt");
    out << "";
    out.close();
    ServerAuthenticator auth;
    char str [19] = "1ttest4700203200\n";
    ASSERT_TRUE(auth.writeUser(str));
}
TEST(serverAuthTests, noDoubleSignUp)
{
    ServerAuthenticator auth;
    char str [19] = "1ttest4700203200\n";
    ASSERT_TRUE(!(auth.writeUser(str)));
}
TEST(serverAuthTests, login)
{
    ServerAuthenticator auth;
    char str [18] = "1ttest4700203200";
    ASSERT_TRUE(auth.isUser(str));
}
int main(int argc, char **argv) {
    
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    return result;
}
