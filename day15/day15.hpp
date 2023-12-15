#ifndef DAY15_HPP
#define DAY15_HPP

#include <string>
#include <algorithm>

#include "../general.hpp"

namespace day15 {
    ll calculate_hash(const std::string& s) {
        ll curr = 0;
        for (char c : s) {
            curr += c;
            curr *= 17;
            curr %= 256;
        }
        return curr;
    }

    struct hashmap {
        std::vector<std::pair<std::string, ll>> contents[256];

        void insert(std::string label, ll value) {
            ll h = calculate_hash(label);
            for (uint i = 0; i < contents[h].size(); i++) {
                if (contents[h][i].first == label) {
                    contents[h][i].second = value;
                    return;
                }
            }
            contents[h].push_back({label, value});
        }

        void remove(const std::string& label) {
            ll h = calculate_hash(label);
            std::erase_if(contents[h], [&](std::pair<std::string, ll> p) { return p.first == label; });
        }

        ll total_focusing_power() {
            ll sum = 0;
            for (uint i = 0; i < 256; i++) {
                for (uint j = 0; j < contents[i].size(); j++) {
                    sum += (i+1)*(j+1)*contents[i][j].second;
                }
            }
            return sum;
        }
    };

}

#endif
