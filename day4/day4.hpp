#ifndef DAY4_HPP
#define DAY4_HPP

#include <vector>
#include <string>
#include <algorithm>

#include "../general.hpp"

namespace day4 {

    std::pair<std::vector<int>, std::vector<int>> get_winning_and_my_numbers(const std::string& line) {
        std::vector<int> winning;
        std::vector<int> mine;
        bool switched = false;
        bool scanning = false;

        std::vector<std::string> tokens = tokenize(line, ":");
        for (std::string& token : tokens) {
            // only register numbers after the colon
            if (token == ":") {
                scanning = true;
                continue;
            }
            if (!scanning) continue;

            if (token == "|") switched = true;
            else {
                int num = std::stoi(token);
                if (switched) mine.push_back(num);
                else winning.push_back(num);
            }
        }

        return {winning, mine};
    }

    int num_winning_cards(const std::vector<int>& winning, const std::vector<int>& mine) {
        int c = 0;
        for (int x : mine) {
            if (std::find(winning.begin(), winning.end(), x) != winning.end()) {
                debug("Found winning %d\n", x);
                c++;
            }
        }
        return c;
    }
}

#endif
