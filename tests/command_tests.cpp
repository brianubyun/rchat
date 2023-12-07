#include "../client/client.h"
#include "../server/server.h"
#include "../client/emojis.h"
#include "../client/client_command_handler.h"
#include "gtest/gtest.h"

/*TEST(CommandTest, standaloneEmoji) {
    std::string expected = ":)";
    std::string message = "//smile";
    EXPECT_EQ(expected, Emoji::ProcessMessage(message));
}

TEST(CommandTest, emojiWithinText) {
    std::string expected = "This is a :), right?";
    std::string message = "This is a //smile, right?";
    EXPECT_EQ(expected, Emoji::ProcessMessage(message));
}

TEST(CommandTest, doubleEmoji) {
    std::string expected = ":):(";
    std::string message = "//smile//sad";
    EXPECT_EQ(expected, Emoji::ProcessMessage(message));
}

TEST(CommandTest, exitCommand) {
    Client dummyClient;
    std::string message = "//exit";
    EXPECT_FALSE(ClientCommandHandler::HandleCommand(message, &dummyClient));
}*/