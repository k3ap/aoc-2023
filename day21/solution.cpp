#include <fstream>

#include "day21.hpp"

int main() {
    std::ifstream ifs("day21/input");
    std::string t;
    day21::gridtype grid;

    while (std::getline(ifs, t)) {
        grid.push_back(t);
    }

    print_solution(1, day21::perform_steps(grid, 64));
    return 0;
}
