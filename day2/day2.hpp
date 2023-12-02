#ifndef DAY2_HPP
#define DAY2_HPP

#include "../general.hpp"

#include <vector>
#include <string>
#include <stdio.h>

namespace day2 {

    struct game {
        int gameid;
        std::vector<int> red_seq;
        std::vector<int> blue_seq;
        std::vector<int> green_seq;
    };

    // Parse a game line as defined in day2
    game parse_game(std::string line) {
        int gameid=-1;
        int last;
        std::vector<int> red, blue, green;
        bool seen[3];
        std::vector<std::string> tokens = tokenize(line + ";", ",;:");
        for (const std::string& token : tokens) {
            if ('0' <= token[0] && token[0] <= '9') {
                int value = std::stoi(token);
                if (gameid == -1) gameid = value;
                else last = value;
            } else if (token == "red") {
                red.push_back(last);
                seen[0] = 1;
            } else if (token == "blue") {
                blue.push_back(last);
                seen[1] = 1;
            } else if (token == "green") {
                green.push_back(last);
                seen[2] = 1;
            } else if (token == ";") {
                if (!seen[0]) red.push_back(0);
                if (!seen[1]) blue.push_back(0);
                if (!seen[2]) green.push_back(0);
                seen[0] = seen[1] = seen[2] = 0;
            }
        }
#if DEBUG
        debug("From string '%s', I made game(%d; ", line.c_str(), gameid);
        for (int i = 0; i < red.size(); i++) {
            printf("%d,%d,%d; ", red[i], blue[i], green[i]);
        }
        putchar(10);
#endif
        return {gameid, red, blue, green};
    }

}

#endif
