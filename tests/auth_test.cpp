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
    ASSErt_TRUE(user.GetPassword().compare("-841574"));
}