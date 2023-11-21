#ifndef EMOJI_H
#define EMOJI_H

#include <string>

class Emoji {
    std::string getEmoji(std::string command)
    {
        if (command == "//test")
            return ("=w=");

        if (command == "//test2")
            return ("=______=");
        
        return "";
    }
};

#endif