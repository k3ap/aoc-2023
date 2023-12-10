#include "day4.hpp"
#include "../general.hpp"

#include <vector>
#include <string>
#include <fstream>

int main() {
    std::ifstream ifs("day04/input");
    std::string line;

    std::vector<int> num_cards(205, 1);
    ll total = 0;
    int idx = 0;
    while (std::getline(ifs, line)) {
        auto[winning, mine] = day4::get_winning_and_my_numbers(line);

        int num_winning = day4::num_winning_cards(winning, mine);
        ll pts = 0;
        for (int i = 0; i < num_winning; i++) {
            if (pts == 0) pts = 1;
            else pts *= 2;
        }
        total += pts;

        for (int i = 0; i < num_winning; i++) {
            num_cards[idx+i+1] += num_cards[idx];
        }
        idx++;
    }
    print_solution(1, total);

    total = 0;
    for (int x : num_cards) total += x;
    print_solution(2, total);

    return 0;
}
