#ifndef DAY11_HPP
#define DAY11_HPP

#include "../general.hpp"

#include <vector>
#include <set>

namespace day11 {
    typedef std::vector<std::vector<char>> gridtype;
    gridtype expand_space(const gridtype& grid) {
        gridtype inter;
        for (uint i = 0; i < grid.size(); i++) {
            inter.push_back({});
            bool empty = true;
            for (uint j = 0; j < grid[i].size(); j++) {
                inter[inter.size()-1].push_back(grid[i][j]);
                if (grid[i][j] == '#') empty = false;
            }
            if (empty) inter.push_back(inter[inter.size()-1]);
        }

        gridtype res;
        for (uint i = 0; i < inter.size(); i++)
            res.push_back({});

        for (uint j = 0; j < inter[0].size(); j++) {
            bool empty = true;
            for (uint i = 0; i < inter.size(); i++) {
                res[i].push_back(inter[i][j]);
                if (inter[i][j] == '#') empty = false;
            }
            if (empty) {
                for (uint i = 0; i < inter.size(); i++) {
                    res[i].push_back('.');
                }
            }
        }
        return res;
    }

    std::vector<cg> find_char(const gridtype& grid, char c) {
        std::vector<cg> res;
        for (uint i = 0; i < grid.size(); i++) {
            for (uint j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == c) res.push_back({i,j});
            }
        }
        return res;
    }

    std::set<uint> empty_columns(const gridtype &grid) {
        std::set<uint> cols;
        for (uint j = 0; j < grid[0].size(); j++) {
            bool empty = true;
            for (uint i = 0; i < grid.size(); i++) {
                if (grid[i][j] == '#')
                    empty = false;
            }
            if (empty)
                cols.insert(j);
        }
        return cols;
    }

    std::set<uint> empty_rows(const gridtype &grid) {
        std::set<uint> rows;
        for (uint i = 0; i < grid.size(); i++) {
            bool empty = true;
            for (uint j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '#')
                    empty = false;
            }
            if (empty)
                rows.insert(i);
        }
        return rows;
    }

    ll distance(cg from, cg to, const std::set<uint>& empty_rows, const std::set<uint>& empty_cols, ll factor) {
        ll dist = 0;
        if (from.i > to.i) std::swap(from, to);
        for (uint i = from.i; i < to.i; i++) {
            if (empty_rows.count(i) != 0) dist += factor;
            else dist++;
        }

        if (from.j > to.j) std::swap(from, to);
        for (uint j = from.j; j < to.j; j++) {
            if (empty_cols.count(j) != 0) dist += factor;
            else dist++;
        }
        return dist;
    }
}

#endif
