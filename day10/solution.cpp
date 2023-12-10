#include <fstream>
#include <vector>
#include <string>

#include "../general.hpp"
#include "day10.hpp"

int main() {
    std::ifstream ifs("day10/input");
    std::vector<std::string> grid;
    std::string t;
    while (std::getline(ifs, t)) grid.push_back(t);
    cg start = day10::find_start(grid);
    std::vector<cg> cycle = day10::find_cycle(grid, start);

    print_solution(1, cycle.size() / 2);

    std::vector<std::vector<int>> bgrid;
    for (uint i = 0; i < grid.size(); i++) {
        bgrid.push_back({});
        bgrid.push_back({});
        for (uint j = 0; j < grid[i].size(); j++) {
            bgrid[2*i].push_back(0);
            bgrid[2*i].push_back(0);
            bgrid[2*i+1].push_back(0);
            bgrid[2*i+1].push_back(0);
        }
    }
    day10::flood(bgrid, {0,0}, 1, grid);
    int cnt = 0;
    for (uint i = 0; i < grid.size(); i++) {
        for (uint j = 0; j < grid[i].size(); j++) {
          if (bgrid[2*i][2*j] == bgrid[2*i][2*j+1] &&
              bgrid[2*i][2*j] == bgrid[2*i+1][2*j] &&
              bgrid[2*i][2*j] == bgrid[2*i+1][2*j+1] &&
              bgrid[2*i][2*j] == 0) cnt++;
        }
    }
    print_solution(2, cnt);

    return 0;
}
