#include "day1.hpp"
#include "../general.hpp"

#include <string>
#include <fstream>

int main() {
    // part 1
    std::ifstream ifs("day1/input");
    std::string t;
    ll sum = 0;
    while (getline(ifs, t)) {
        std::pair<int, int> first_last = day1::get_first_and_last_digit(t);
        sum += first_last.first * 10 + first_last.second;
    }
    print_solution(1, sum);
    ifs.close();

    // part 2
    ifs.open("day1/input");
    sum = 0;
    while (getline(ifs, t)) {
        std::pair<int, int> first_last = day1::get_first_and_last_number(t);
        sum += first_last.first * 10 + first_last.second;
    }
    print_solution(2, sum);
    ifs.close();

    return 0;
}
