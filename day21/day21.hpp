#ifndef DAY21_HPP
#define DAY21_HPP

#include <set>

#include "../general.hpp"

#define O(idx) (((idx)+1)%2)

namespace day21 {
    typedef std::vector<std::string> gridtype;
    typedef std::vector<std::vector<int>> auxgridtype;

    cg find_start(const gridtype& grid) {
        for (uint i = 0; i < grid.size(); i++) {
            for (uint j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 'S') {
                    return {i,j};
                }
            }
        }
        return {0,0};
    }

    ll perform_steps(const gridtype& grid, int max_dist) {
        cg start = find_start(grid);
        std::set<cg> nodes[2];
        int idx = 0;
        nodes[idx].insert(start);
        for (int dist = 1; dist <= max_dist; dist++) {
            for (cg x : nodes[idx]) {
                for (cg y : x.adjacent4(grid.size(), grid[0].size())) {
                    if (grid AT(y) == '#') continue;
                    nodes[O(idx)].insert(y);
                }
            }
            nodes[idx].clear();
            idx = O(idx);
        }
        return nodes[idx].size();
    }
}

#endif
