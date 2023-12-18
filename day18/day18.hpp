#ifndef DAY18_HPP
#define DAY18_HPP

#include <string>
#include <vector>
#include <queue>

#include "../general.hpp"

namespace day18 {
    Direction udrl_to_direction(char c) {
        switch(c) {
        case 'U': return north;
        case 'D': return south;
        case 'L': return west;
        case 'R': return east;
        }
        throw 1;
    }

    struct Instruction {
        Direction dir;
        int length;
        std::string color;

        Instruction flipped() const {
            int len = 0;
            for (int i = 0; i < 5; i++) {
                len *= 16;
                if (color[i] >= 'a') len += color[i] - 'a' + 10;
                else len += color[i]-'0';
            }
            Direction newdir;
            switch(color[5]) {
            case '0': newdir = east; break;
            case '1': newdir = south; break;
            case '2': newdir = west; break;
            case '3': newdir = north; break;
            }
            return {newdir, len, ""};
        }
    };

    void floodfill(std::vector<std::vector<char>>& grid, cg start) {
        std::queue<cg> q;
        q.push(start);
        grid AT(start) = '+';
        while (!q.empty()) {
            cg x = q.front();
            q.pop();
            for (cg y : x.adjacent4(grid.size(), grid[0].size())) {
                if (grid AT(y) == '.') {
                    grid AT(y) = '+';
                    q.push(y);
                }
            }
        }
    }
}

#endif
