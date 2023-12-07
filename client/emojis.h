#ifndef EMOJI_H
#define EMOJI_H

#include <string>
#include <algorithm>

class Emoji {
public:
    static std::string ProcessMessage(std::string message) {
        ReplaceCommandWithEmoji(message, "//smile", ":)");
        ReplaceCommandWithEmoji(message, "//sad", ":(");
        ReplaceCommandWithEmoji(message, "//angry", ">:(");
        ReplaceCommandWithEmoji(message, "//sus", "':\\");
        return message;
    }

private:
    static void ReplaceCommandWithEmoji(std::string& message, const std::string& command, const std::string& emoji) {
        int position = 0;
        while ((position = message.find(command, position)) != std::string::npos) {
            message.replace(position, command.length(), emoji);
            position += emoji.length();
        }
    }
};

#endif
