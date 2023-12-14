#ifndef DAY14_HPP
#define DAY14_HPP

#include <vector>
#include <unordered_map>
#include <string>

#include "../general.hpp"

namespace day14 {
    typedef std::vector<std::string> gridtype;

    void tilt_table(Direction dir, gridtype& grid) {
        if (dir == north || dir == south) {
            std::vector<uint> roll_result(grid[0].size(), ((dir == north) ? 0 : grid[0].size()-1));
            for (uint i = ((dir == north) ? 0 : grid.size()-1); i < grid.size(); i = i + ((dir == north) ? 1 : -1)) {
                for (uint j = 0; j < grid[i].size(); j++) {

                    if (grid[i][j] == '#')
                        roll_result[j] = i + ((dir == north) ? 1 : -1);
                    else if (grid[i][j] == 'O') {
                        grid[roll_result[j]][j] = 'O';
                        if (roll_result[j] != i) grid[i][j] = '.';
                        roll_result[j] = roll_result[j] + ((dir == north) ? 1 : -1);
                    }
                }
            }
        } else {
            std::vector<uint> roll_result(grid.size(), ((dir == west) ? 0 : grid.size()-1));
            for (uint j = ((dir == west) ? 0 : grid[0].size()-1); j < grid[0].size(); j = j + ((dir == west) ? 1 : -1)) {
                for (uint i = 0; i < grid.size(); i++) {
                    if (grid[i][j] == '#')
                        roll_result[i] = j + (dir == west ? 1 : -1);
                    else if (grid[i][j] == 'O') {
                        grid[i][roll_result[i]] = 'O';
                        if (roll_result[i] != j) grid[i][j] = '.';
                        roll_result[i] = roll_result[i] + (dir == west ? 1 : -1);
                    }
                }
            }
        }
    }

    ll calculate_load(const gridtype& grid) {
        ll sum = 0;
        for (uint i = 0; i < grid.size(); i++) {
            for (uint j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 'O')
                    sum += grid.size()-i;
            }
        }
        return sum;
    }

    bool compare_grids(const gridtype& g1, const gridtype& g2) {
        for (uint i = 0; i < g1.size(); i++) {
            for (uint j = 0; j < g1[i].size(); j++) {
                if (g1[i][j] != g2[i][j]) return false;
            }
        }
        return true;
    }

    void cycle(gridtype &grid) {
        tilt_table(north, grid);
        tilt_table(west, grid);
        tilt_table(south, grid);
        tilt_table(east, grid);
    }

    // big prime
    const ll M = 100000000003ll;

    ll hash_grid(const gridtype& grid) {
        ll x = 0;
        std::hash<std::string> hasher;
        for (const std::string& s : grid) {
            x += hasher(s);
            x %= M;
        }
        return x;
    }
}

#endif
