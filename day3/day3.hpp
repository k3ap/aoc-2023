#ifndef DAY3_HPP
#define DAY3_HPP

#include <vector>
#include <string>

namespace day3 {

    // Find all numbers which are adjacent to a special symbol, and which symbol they're adjacent to.
    // This function assumes that grid[:][-1] is a vector of dots.
    std::pair<std::vector<int>, std::vector<std::vector<cg>>> find_adjacent_numbers(const std::vector<std::string>& grid, const std::string& special) {
        std::vector<int> numbers;
        std::vector<std::vector<cg>> adjacencies;
        std::string num = "";
        std::vector<cg> adjacent;
        for (uint i = 0; i < grid.size(); i++) {
            for (uint j = 0; j < grid[i].length(); j++) {

                if ('0' <= grid[i][j] && grid[i][j] <= '9') {
                    num += grid[i][j];

                    if (j > 0 && num.length() == 1) {
                        if (special.find(grid[i][j-1]) != std::string::npos) adjacent.push_back({i, j-1});
                        if (i > 0 && special.find(grid[i-1][j-1]) != std::string::npos) adjacent.push_back({i-1, j-1});
                        if (i < grid.size()-1 && special.find(grid[i+1][j-1]) != std::string::npos) adjacent.push_back({i+1, j-1});
                    }

                }

                if (num.length() > 0) {
                    if (special.find(grid[i][j]) != std::string::npos) adjacent.push_back({i, j});
                    if (i > 0 && special.find(grid[i-1][j]) != std::string::npos) adjacent.push_back({i-1, j});
                    if (i < grid.size()-1 && special.find(grid[i+1][j]) != std::string::npos) adjacent.push_back({i+1, j});
                }

                if (!('0' <= grid[i][j] && grid[i][j] <= '9')) {
                    // this is not a number; we ignore it, unless it's the end of a number string
                    if (num.length() > 0) {
                        debug("Adjacent to %d: ", std::stoi(num));
                        for (cg c : adjacent) {
                            debug2("%d,%d ", c.i, c.j);
                        }
                        debug2("\n");
                    }
                    if (num.length() > 0 && adjacent.size() > 0) {
                        numbers.push_back(std::stoi(num));
                        adjacencies.push_back(adjacent);
                    }
                    num = "";
                    adjacent.clear();
                }

            }
        }
        return {numbers, adjacencies};
    }
}

#endif
