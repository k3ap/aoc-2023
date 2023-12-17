#include <fstream>

#include "../general.hpp"
#include "day17.hpp"

int main() {
    std::ifstream ifs("day17/input");
    day17::gridtype grid;
    std::string t;
    while (std::getline(ifs, t)) {
        grid.push_back({});
        for (char c : t) {
            grid[grid.size() - 1].push_back(c - '0');
        }
    }
    print_solution(1, day17::find_path(grid));
    print_solution(2, day17::find_path(grid, true));

    return 0;
}
