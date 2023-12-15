#include <fstream>
#include <string>
#include <vector>

#include "../general.hpp"
#include "day15.hpp"

int main() {
    std::ifstream ifs("day15/input");
    std::string t;
    std::getline(ifs, t);
    std::vector<std::string> tokens = tokenize(t, "", " \t\n,");

    ll sum = 0;
    for (const std::string& s : tokens) {
        sum += day15::calculate_hash(s);
    }
    print_solution(1, sum);

    day15::hashmap hm;
    tokens = tokenize(t, "-=", " \t\n,");
    std::string last;
    bool adding = false;
    for (std::string s : tokens) {
        if (s == "=") {
            adding = true;
        } else if (s == "-") {
            hm.remove(last);
        } else if (adding) {
            hm.insert(last, std::stoll(s));
            adding = false;
        } else {
            last = s;
        }
    }
    print_solution(2, hm.total_focusing_power());

    return 0;
}
