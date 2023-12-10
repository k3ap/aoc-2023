#include <fstream>

#include "../general.hpp"
#include "day9.hpp"

int main() {
    std::ifstream ifs("day09/input");
    ll sum1 = 0, sum2 = 0;
    std::string t;
    while (std::getline(ifs, t)) {
        std::vector<std::string> tokens = tokenize(t);
        std::vector<ll> seq;
        for (std::string s : tokens)
            seq.push_back(std::stoll(s));
        auto [x1, x2] = day9::predict_sequence(seq);
        sum1 += x1;
        sum2 += x2;
    }
    print_solution(1, sum1);
    print_solution(2, sum2);
    return 0;
}
