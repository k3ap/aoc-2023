#include "../general.hpp"
#include "day3.hpp"

#include <fstream>
#include <vector>
#include <string>
#include <map>

int main() {
    std::ifstream ifs("day03/input");
    std::vector<std::string> grid;
    std::string t;
    while (getline(ifs, t))
        grid.push_back(t);

    std::string special = "#$%&*+-/=@";

    // add dots at the end of the grid to simplify parsing
    for (uint i = 0; i < grid.size(); i++) {
        grid[i] += ".";
    }

    auto[numbers, adjacencies] = day3::find_adjacent_numbers(grid, special);

    debug("Found numbers:\n");
    for (int x : numbers) {
        debug("%d\n", x);
    }

    ll sum = 0;
    for (int x : numbers) sum += x;
    print_solution(1, sum);

    std::map<cg, std::vector<int>> adjacent;
    for (uint i = 0; i < numbers.size(); i++) {
        for (cg c : adjacencies[i]) {
            adjacent[c].push_back(numbers[i]);
        }
    }

    sum = 0;
    for (auto&[c, vec] : adjacent) {
        if (grid AT(c) != '*') continue;
        if (vec.size() != 2) continue;
        sum += vec[0] * vec[1];
    }
    print_solution(2, sum);

    return 0;
}
