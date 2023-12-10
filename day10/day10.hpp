#ifndef DAY10_HPP
#define DAY10_HPP

#include "../general.hpp"

#include <vector>
#include <string>
#include <queue>
#include <map>

namespace day10 {
    cg find_start(const std::vector<std::string>& grid) {
        for (uint i = 0; i < grid.size(); i++) {
            for (uint j = 0; j < grid[i].length(); j++) {
                if (grid[i][j] == 'S') return {i, j};
            }
        }
        return {0,0};
    }

    typedef const std::vector<std::string>& gridtype;

    bool left_connection(char c) {
        return c == '-' || c == 'J' || c == '7' || c == 'S';
    }

    bool right_connection(char c) {
        return c == '-' || c == 'L' || c == 'F' || c == 'S';
    }

    bool up_connection(char c) {
        return c == '|' || c == 'L' || c == 'J' || c == 'S';
    }

    bool down_connection(char c) {
        return c == '|' || c == '7' || c == 'F' || c == 'S';
    }

    bool can_go(gridtype grid, cg from, cg to) {
        // if we go too far left, the coordinate overflows and is detected by this
        if (to.i >= grid.size() || to.j >= grid[0].length()) return false;
        if (to.i == from.i && to.j == from.j + 1) {
            return right_connection(grid AT(from)) && left_connection(grid AT(to));
        }
        if (to.i == from.i && to.j == from.j-1) {
            return left_connection(grid AT(from)) && right_connection(grid AT(to));
        }
        if (to.j == from.j && to.i == from.i + 1) {
            return down_connection(grid AT(from)) && up_connection(grid AT(to));
        }
        if (to.j == from.j && to.i == from.i - 1) {
            return up_connection(grid AT(from)) && down_connection(grid AT(to));
        }
        return false;
    }

    void _dfs(gridtype grid, cg curr, std::map<cg, cg>& parent, cg start, cg& end) {
        debug("curr: %d,%d\n", curr.i, curr.j);
        for (cg adj : curr.adjacent4(grid.size(), grid[0].length())) {
            if (!can_go(grid, curr, adj))
                continue;
            if (adj == start && parent[curr] != start) {
              debug("New end: %d,%d\n", curr.i, curr.j);
              end = curr;
            }
            if (parent.count(adj) == 0) {
              parent[adj] = curr;
              _dfs(grid, adj, parent, start, end);
            }
        }
    }

    std::vector<cg> find_cycle(gridtype grid, cg start) {
        std::map<cg, cg> parent;
        cg end;
        parent[start] = start;

        _dfs(grid, start, parent, start, end);

        std::vector<cg> res;
        res.push_back(end);
        while (end != start) {
            end = parent[end];
            res.push_back(end);
        }
        debug("start was %d,%d\n", start.i, start.j);
        debug("res: ");
        for (cg x : res)
            debug2("%d,%d ", x.i, x.j);
        debug2("\n");
        return res;
    }

    bool can_cross(cg from, cg to, gridtype reference) {
        cg fromr = {from.i / 2, from.j / 2};
        cg tor = {to.i / 2, to.j / 2};
        if (fromr != tor) return true;
        cg exc;
        switch (reference AT(fromr)) {
        case '|':
            return from.j == to.j;
        case '-':
            return from.i == to.i;
        case 'L':
            exc = {fromr.i*2, fromr.j*2+1};
            return from != exc && to != exc;
        case 'J':
            exc = {fromr.i * 2, fromr.j * 2};
            return from != exc && to != exc;
        case '7':
            exc = {fromr.i * 2+1, fromr.j * 2};
            return from != exc && to != exc;
        case 'F':
            exc = {fromr.i *2+1, fromr.j*2+1};
            return from != exc && to != exc;
        }
        return false;
    }

    void flood(std::vector<std::vector<int>> &grid, cg start, int color, gridtype reference) {
        std::queue<cg> q;
        q.push(start);
        while (!q.empty()) {
            cg curr = q.front();
            q.pop();
            for (cg adj : curr.adjacent4(grid.size(), grid[0].size())) {
                if (grid AT(adj) != 0 || !can_cross(curr, adj, reference))
                    continue;
                grid AT(adj) = color;
                q.push(adj);
            }
        }
    }
}

#endif
