#ifndef EMOJI_H
#define EMOJI_H

#include <string>
#include <algorithm>

class Emoji {
public:
    // function that actually processes the message
    // it unfortunately checks EVERY emoji EVERY message it sends
    // TODO: Only have it call the function if // is used
    static std::string ProcessMessage(std::string message) {
        ReplaceCommandWithEmoji(message, "//test", "=w=");
        ReplaceCommandWithEmoji(message, "//test2", "=______=");
        return message;
    }

private:
    // message, command, and emoji
    static void ReplaceCommandWithEmoji(std::string& message, const std::string& command, const std::string& emoji) {
        int position = 0;
        // npos is not-position, but C++ can also interpret it to mean [end of a string]
        while ((position = message.find(command, position)) != std::string::npos) {
                message.replace(position, command.length(), emoji);
                position += emoji.length();
        }
    }
};

#endif
