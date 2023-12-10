#include <fstream>
#include <vector>
#include <algorithm>

#include "day7.hpp"
#include "../general.hpp"

int main() {
    std::ifstream ifs("day07/input");
    std::vector<std::pair<day7::hand, int>> data;
    std::string t;
    while (std::getline(ifs, t)) {
        std::vector<std::string> tokens = tokenize(t);
        data.push_back({day7::hand({tokens[0]}), std::stoi(tokens[1])});
    }
    sort(data.begin(), data.end());
    ll res = 0;
    for (uint i = 0; i < data.size(); i++) {
        res += (i+1) * data[i].second;
    }
    print_solution(1, res);

    day7::generate_replacements();
    sort(data.begin(), data.end(), day7::cmpr_joker);
    res = 0;
    for (uint i = 0; i < data.size(); i++) {
        res += (i+1) * data[i].second;
    }
    print_solution(2, res);

    return 0;
}
