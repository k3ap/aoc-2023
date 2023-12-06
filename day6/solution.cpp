#include "../general.hpp"
#include "day6.hpp"

#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ifstream ifs("day6/input");

    std::string s1, s2;
    getline(ifs, s1);
    getline(ifs, s2);

    std::vector<std::string> tokens1 = tokenize(s1);
    std::vector<std::string> tokens2 = tokenize(s2);

    std::vector<ll> times;
    std::vector<ll> distances;

    std::string big_time = "";
    std::string big_distance = "";

    for (uint i = 1; i < tokens1.size(); i++) {
        times.push_back(std::stoll(tokens1[i]));
        distances.push_back(std::stoll(tokens2[i]));
        big_time += tokens1[i];
        big_distance += tokens2[i];
    }

    ll prod = 1;
    for (uint i = 0; i < times.size(); i++) {
        prod *= day6::ways_to_break_record(times[i], distances[i]);
    }
    print_solution(1, prod);

    print_solution(2, day6::ways_to_break_record(std::stoll(big_time), std::stoll(big_distance)));

    return 0;
}
