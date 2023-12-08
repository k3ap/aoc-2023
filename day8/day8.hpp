#ifndef DAY8_HPP
#define DAY8_HPP

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

#include "../general.hpp"

namespace day8 {
    struct LRgraph {
        std::map<std::string, std::pair<std::string, std::string>> ins;

        std::string left_of(std::string s) {
            return ins[s].first;
        }

        std::string right_of(std::string s) {
            return ins[s].second;
        }

        // Get all nodes whose names end in A
        std::vector<std::string> get_all_A_suffix() {
            std::vector<std::string> rvl;
            for (auto&[k, v] : ins) {
                if (k[k.length() - 1] == 'A') rvl.push_back(k);
            }
            return rvl;
        }
    };

    LRgraph parse_graph(std::ifstream& ifs) {
        std::string t;
        std::map<std::string, std::pair<std::string, std::string>> m;
        while (std::getline(ifs, t)) {
            std::vector<std::string> tokens = tokenize(t, "=(,)");
            m[tokens[0]] = {tokens[3], tokens[5]};
        }
        return LRgraph({m});
    }

    int get_num_steps(LRgraph graph, std::string instructions, std::string starting="AAA", bool check_all=true) {
        int cnt = 0;
        int idx = 0;
        std::string curr = starting;
        while ((check_all && curr != "ZZZ") || (!check_all && curr[2] != 'Z')) {
            cnt++;
            if (instructions[idx] == 'L') curr = graph.left_of(curr);
            else curr = graph.right_of(curr);
            idx++;  idx %= instructions.length();
        }
        return cnt;
    }
}

#endif
