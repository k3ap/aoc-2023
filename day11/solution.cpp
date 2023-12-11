#include <fstream>
#include <set>

#include "../general.hpp"
#include "day11.hpp"

int main() {
    std::ifstream ifs("day11/input");
    day11::gridtype grid;
    std::string t;
    while (std::getline(ifs, t)) {
        grid.push_back({});
        for (uint i = 0; i < t.length(); i++) {
            grid[grid.size()-1].push_back(t[i]);
        }
    }
    day11::gridtype expanded = day11::expand_space(grid);

    debug("Expanded grid:\n");
    for (uint i = 0; i < expanded.size(); i++) {
        debug("");
        for (uint j = 0; j < expanded[i].size(); j++) {
            debug2("%c", expanded[i][j]);
        }
        debug2("\n");
    }
    std::vector<cg> coords = day11::find_char(expanded, '#');
    ll sum = 0;
    for (cg x : coords) {
        for (cg y : coords) {
            sum += x.manhattan(y);
        }
    }
    print_solution(1, sum/2);

    std::set<uint> empty_cols = day11::empty_columns(grid);
    std::set<uint> empty_rows = day11::empty_rows(grid);

    debug("Empty rows: ");
    for (uint x : empty_rows) debug2("%d ", x);
    debug2("\n");

    coords = day11::find_char(grid, '#');

    sum = 0;
    for (cg x : coords) {
        for (cg y : coords) {
            ll dist = day11::distance(x, y, empty_rows, empty_cols, 1000000);
            debug("Distance between %d,%d and %d,%d is %lld\n", x.i, x.j, y.i, y.j, dist);
            sum += dist;
        }
    }
    print_solution(2, sum/2);

    return 0;
}

