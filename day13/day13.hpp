#ifndef DAY13_HPP
#define DAY13_HPP

#include <vector>
#include <string>

#include "../general.hpp"

namespace day13 {
    typedef std::vector<std::string> gridtype;

    // whether or not the grid is reflected after the given row
    bool is_reflection_after_row(int row, const gridtype &grid) {
        int offs = 0;
        while (row - offs >= 0 && (int) grid.size() > row + 1 + offs) {
            for (uint j = 0; j < grid[row].size(); j++) {
                if (grid[row - offs][j] != grid[row + 1 + offs][j]) return false;
            }
            offs++;
        }
        return true;
    }

    // whether or not the grid is reflected after the given column
    bool is_reflection_after_column(int col, const gridtype& grid) {
        int offs = 0;
        while (col - offs >= 0 && (int) grid[0].size() > col + 1 + offs) {
            for (uint i = 0; i < grid.size(); i++) {
                if (grid[i][col-offs] != grid[i][col+1+offs]) return false;
            }
            offs++;
        }
        return true;
    }

    std::pair<std::vector<int>, std::vector<int>> find_all_reflections(const gridtype& grid) {
        std::vector<int> rowr, colr;
        for (uint row = 0; row < grid.size() - 1; row++) {
            if (is_reflection_after_row(row, grid)) {
                rowr.push_back(row+1);
                debug("Found reflection in row %d\n", row);
            }
        }
        for (uint col = 0; col < grid[0].size() - 1; col++) {
            if (is_reflection_after_column(col, grid)) {
                colr.push_back(col+1);
                debug("Found reflection in col %d\n", col);
            }
        }
        return {rowr, colr};
    }

    ll find_reflections(const gridtype &grid) {
        ll sum = 0;
        auto [rowr, colr] = find_all_reflections(grid);
        for (int row : rowr) sum += row * 100;
        for (int col : colr) sum += col;
        return sum;
    }

    void flip(gridtype &grid, uint i, uint j) {
        if (grid[i][j] == '.')
            grid[i][j] = '#';
        else
            grid[i][j] = '.';
    }

    ll find_smudge_reflections(gridtype &grid) {
        ll sum = 0;
        for (uint i = 0; i < grid.size(); i++) {
            for (uint j = 0; j < grid[i].size(); j++) {
                auto [rowr, colr] = find_all_reflections(grid);
                flip(grid, i, j);
                auto [rowrf, colrf] = find_all_reflections(grid);
                flip(grid, i, j);

                debug("For bit flip %d,%d, rowr=", i, j);
                for (int x : rowr) debug2("%d,", x);
                debug2(", colr=");
                for (int x : colr) debug2("%d,", x);
                debug2(", colr=");
                for (int x : colr) debug2("%d,", x);
                debug2(", rowrf=");
                for (int x : rowrf) debug2("%d,", x);
                debug2(", colrf=");
                for (int x : colrf) debug2("%d,", x);
                debug2("\n");


                uint i1=0, i2=0;
                while (i1 < rowr.size() && i2 < rowrf.size()) {
                    if (rowr[i1] == rowrf[i2]) {
                        i1++; i2++;
                    } else if (rowr[i1] < rowrf[i2]) {
                        i1++;
                    } else {
                        sum += 100 * rowrf[i2];
                        i2++;
                    }
                }
                while (i2 < rowrf.size()) sum += 100 * rowrf[i2++];

                i1 = 0, i2 = 0;
                while (i1 < colr.size() && i2 < colrf.size()) {
                    if (colr[i1] == colrf[i2]) {
                        i1++; i2++;
                    } else if (colr[i1] < colrf[i2]) {
                        i1++;
                    } else {
                        sum += colrf[i2];
                        i2++;
                    }
                }
                while (i2 < colrf.size()) sum += colrf[i2++];
            }
        }
        return sum;
    }
}

#endif
