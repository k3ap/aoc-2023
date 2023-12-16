#ifndef DAY16_HPP
#define DAY16_HPP

#include <vector>
#include <string>
#include <map>

#include "../general.hpp"

namespace day16 {
    typedef std::vector<std::string> gridtype;
    typedef std::vector<std::vector<int>> auxgridtype;
    typedef std::map<std::pair<Direction, cg>, bool> seentype;

    // walk through the grid per instructions
    // paint all visited indicies in aux with 1
    // x is the current position, dir is the direction the light is traveling to
    void dfs(const gridtype& grid, auxgridtype& aux, seentype& seen, Direction dir, cg x) {
        if (seen.count({dir, x}) != 0 && seen[{dir, x}]) return;
        seen[{dir, x}] = true;
        debug("dfs(dir=%c, i=%d, j=%d)\n", dir, x.i, x.j);
        aux AT(x) = 1;
        Direction newdir;
        switch (grid AT(x)) {
        case '.':
            if (x.can_follow(dir, grid.size(), grid[0].size())) dfs(grid, aux, seen, dir, x.follow(dir));
            break;
        case '/':
            switch (dir) {
            case north:
                newdir = east;
                break;
            case south:
                newdir = west;
                break;
            case east:
                newdir = north;
                break;
            case west:
                newdir = south;
                break;
            }
            if (x.can_follow(newdir, grid.size(), grid[0].size())) dfs(grid, aux, seen, newdir, x.follow(newdir));
            break;
        case '\\':
            switch (dir) {
            case north:
                newdir = west;
                break;
            case south:
                newdir = east;
                break;
            case east:
                newdir = south;
                break;
            case west:
                newdir = north;
                break;
            }
            if (x.can_follow(newdir, grid.size(), grid[0].size())) dfs(grid, aux, seen, newdir, x.follow(newdir));
            break;
        case '|':
            if (dir == north || dir == south) {
                if (x.can_follow(dir, grid.size(), grid[0].size())) dfs(grid, aux, seen, dir, x.follow(dir));
            } else {
                if (x.can_follow(north, grid.size(), grid[0].size())) dfs(grid, aux, seen, north, x.follow(north));
                if (x.can_follow(south, grid.size(), grid[0].size())) dfs(grid, aux, seen, south, x.follow(south));
            }
            break;
        case '-':
            if (dir == east || dir == west) {
                if (x.can_follow(dir, grid.size(), grid[0].size())) dfs(grid, aux, seen, dir, x.follow(dir));
            } else {
                if (x.can_follow(east, grid.size(), grid[0].size())) dfs(grid, aux, seen, east, x.follow(east));
                if (x.can_follow(west, grid.size(), grid[0].size())) dfs(grid, aux, seen, west, x.follow(west));
            }
            break;
        }
    }
}

#endif
