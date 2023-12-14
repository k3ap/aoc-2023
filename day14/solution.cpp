#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../general.hpp"
#include "day14.hpp"

int main() {
    day14::gridtype grid;
    std::ifstream ifs("day14/input");
    std::string t;
    while (std::getline(ifs, t)) {
        grid.push_back(t);
    }
    day14::tilt_table(north, grid);
    debug("grid after north tilt:\n");
    for (std::string &s : grid) {
        debug("%s\n", s.c_str());
    }
    print_solution(1, day14::calculate_load(grid));

    grid.clear();
    ifs.close();
    ifs.open("day14/input");
    while (std::getline(ifs, t)) {
        grid.push_back(t);
    }
    std::map<ll, int> found_hashes;
    ll hash = day14::hash_grid(grid);
    int cycles = 0;
    while (found_hashes.count(hash) == 0) {
        found_hashes[hash] = cycles++;
        day14::cycle(grid);
        hash = day14::hash_grid(grid);
    }
    debug("Looped after %d cycles\n", cycles);
    ll offs = found_hashes[hash];
    ll diff = cycles - offs;
    while (cycles + diff < 1000000000) {
        cycles += diff;
    }
    while (cycles < 1000000000) {
        day14::cycle(grid);
        cycles++;
    }
    debug("Grid at the end:\n");
    for (const std::string& s : grid) {
        debug("%s\n", s.c_str());
    }
    print_solution(2, day14::calculate_load(grid));
    return 0;
}
