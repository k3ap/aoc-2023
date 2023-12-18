#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "../general.hpp"
#include "day18.hpp"

int main() {
    std::ifstream ifs("day18/input");
    std::vector<day18::Instruction> instructions;
    std::string t;
    while (std::getline(ifs, t)) {
        std::vector<std::string> tokens = tokenize(t, "", " \t\n()#");
        instructions.push_back({day18::udrl_to_direction(tokens[0][0]),
                                std::stoi(tokens[1]), tokens[2]});
    }

    c2 curr = {0, 0};
    offsetgrid<char> grid('.');
    for (day18::Instruction ins : instructions) {
        for (int i = 0; i < ins.length; i++) {
            curr = curr.follow(ins.dir);
            grid.set(curr, '#');
        }
    }

    debug_draw_offsetgrid(grid);

    auto pgrid = grid.get_grid();
    for (uint i = 0; i < pgrid.size(); i++) {
        if (pgrid[i][0] == '.')
            day18::floodfill(pgrid, {i,0});
        if (pgrid[i][pgrid[i].size()-1] == '.')
            day18::floodfill(pgrid, {i, (uint) pgrid[i].size()-1});
    }
    for (uint j = 0; j < pgrid[0].size(); j++) {
        if (pgrid[0][j] == '.')
            day18::floodfill(pgrid, {0,j});
        if (pgrid[pgrid.size()-1][j] == '.')
            day18::floodfill(pgrid, {(uint) pgrid.size()-1, j});
    }
    ll cnt = 0;
    for (uint i = 0; i < pgrid.size(); i++) {
        for (uint j = 0; j < pgrid[i].size(); j++) {
            if (pgrid[i][j] != '+') cnt++;
        }
    }
    print_solution(1, cnt);

    std::vector<day18::Instruction> new_instructions;
    for (day18::Instruction ins : instructions) {
        new_instructions.push_back(ins.flipped());
    }

    curr = {0,0};
    day18::Instruction last = new_instructions[new_instructions.size()-1];
    c2 prev = curr.follow(get_opposite(last.dir), last.length);
    ll area = 0;
    ll perimeter = 0;
    ll corners = 0;
    for (day18::Instruction ins : new_instructions) {
        perimeter += ins.length-1;
        c2 new_curr = curr.follow(ins.dir, ins.length);
        area += (curr.x - new_curr.x) * (curr.y + new_curr.y) / 2;
        if ((curr-prev).cross(new_curr-curr) > 0) {
            corners += 3;
        } else {
            corners += 1;
        }
        prev = curr;
        curr = new_curr;
    }
    debug("curr: %lld,%lld\n", curr.x, curr.y);
    debug("Area: %lld, perimeter: %lld, corners: %lld\n", area, perimeter, corners);
    print_solution(2, area + perimeter/2 + corners/4);

    return 0;
}
