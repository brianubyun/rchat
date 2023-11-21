#ifndef EMOJI_H
#define EMOJI_H

#include <string>

class Emoji {
    std::string getEmoji(std::string command)
    {
        if (command == "//test")
            return ("=w=");
        return "";
    }
};

#endif