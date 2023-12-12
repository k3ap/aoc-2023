#include <fstream>
#include <vector>
#include <string>

#include "../general.hpp"
#include "day12.hpp"

int main() {
    std::ifstream ifs("day12/input");
    std::string t;
    ll sum1 = 0;
    ll sum2 = 0;
    while (std::getline(ifs, t)) {
        std::vector<std::string> tokens = tokenize(t, "", " \t\n,");
        std::string desc = tokens[0];
        std::vector<int> groups;
        for (uint i = 1; i < tokens.size(); i++)
            groups.push_back(std::stoi(tokens[i]));

        std::map<day12::dp_state, ll> memo;
        ll cnt = 0;
        uint i = 0;
        for (; i < desc.length() && desc[i] != '#'; i++) {
            if (desc[i] == '?')
                cnt +=
                    day12::count_possibilities_dp(desc, groups, {i, 0}, memo);
        }
        if (i < desc.length())
            cnt += day12::count_possibilities_dp(desc, groups, {i, 0}, memo);

        debug("For %s, I found %lld matches.\n", desc.c_str(), cnt);
        sum1 += cnt;

        std::string new_desc;
        for (int i = 0; i < 5; i++) {
            if (i > 0) new_desc += '?';
            new_desc += desc;
        }
        std::vector<int> new_groups;
        for (int j = 0; j < 5; j++) {
            for (uint i = 0; i < groups.size(); i++)
                new_groups.push_back(groups[i]);
        }
        memo.clear();
        cnt = 0;
        i = 0;
        for (; i < new_desc.length() && new_desc[i] != '#'; i++) {
            if (new_desc[i] == '?')
                cnt +=
                    day12::count_possibilities_dp(new_desc, new_groups, {i, 0}, memo);
        }
        if (i < new_desc.length())
            cnt += day12::count_possibilities_dp(new_desc, new_groups, {i, 0}, memo);

        debug("[P2] For %s, I found %lld matches.\n", new_desc.c_str(), cnt);
        sum2 += cnt;
    }
    print_solution(1, sum1);
    print_solution(2, sum2);
    return 0;
}
