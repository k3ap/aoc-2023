#include <fstream>

#include "../general.hpp"
#include "day16.hpp"

day16::auxgridtype make_aux(const day16::gridtype& grid) {
    day16::auxgridtype aux;
    for (uint i = 0; i < grid.size(); i++) {
        std::vector<int> zeros(grid[i].size(), 0);
        aux.push_back(zeros);
    }
    return aux;
}

ll count_ones(const day16::auxgridtype& aux) {
    ll cnt = 0;
    for (uint i = 0; i < aux.size(); i++) {
        for (uint j = 0; j < aux[i].size(); j++) {
            if (aux[i][j] == 1) cnt++;
        }
    }
    return cnt;
}

int main() {
    std::ifstream ifs("day16/input");
    std::string t;
    day16::gridtype grid;
    while (std::getline(ifs, t)) {
        grid.push_back(t);
    }
    day16::auxgridtype aux = make_aux(grid);
    day16::seentype seen;
    day16::dfs(grid, aux, seen, east, {0, 0});
    ll cnt = count_ones(aux);
    print_solution(1, cnt);

    ll best = cnt;
    for (uint i = 0; i < grid.size(); i++) {
        aux = make_aux(grid);
        seen.clear();
        day16::dfs(grid, aux, seen, east, {i, 0});
        best = std::max(best, count_ones(aux));
        aux = make_aux(grid);
        seen.clear();
        day16::dfs(grid, aux, seen, west, {i, (uint) grid[i].size()-1});
        best = std::max(best, count_ones(aux));
    }

    for (uint j = 0; j < grid[0].size(); j++) {
        aux = make_aux(grid);
        seen.clear();
        day16::dfs(grid, aux, seen, south, {0, j});
        best = std::max(best, count_ones(aux));
        aux = make_aux(grid);
        seen.clear();
        day16::dfs(grid, aux, seen, north, {(uint) grid.size()-1, j});
        best = std::max(best, count_ones(aux));
    }

    print_solution(2, best);
    return 0;
}
