#include "../client/client.h"
#include "../server/server.h"
#include "gtest/gtest.h"

TEST(CommandTest, standaloneEmoji) {
    char buffer[] = "//test";
    EXPECT_EQ();
}

TEST(CommandTest, emojiWithinText) {
    char buffer[] = "This is a //test, right?";
    EXPECT_EQ();
}

TEST(CommandTest, doubleEmoji) {
    char buffer[] = "//test//test2";
    EXPECT_EQ();
}

TEST(CommandTest, exitCommand) {
    char buffer[] = "//exit";
    EXPECT_EQ();
}