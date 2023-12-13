#include <string>
#include <vector>
#include <fstream>

#include "../general.hpp"
#include "day13.hpp"

int main() {
    std::ifstream ifs("day13/input");
    day13::gridtype grid;
    std::string t;
    ll sum1 = 0, sum2 = 0;
    while (std::getline(ifs, t)) {
        if (t.length() > 0)
            grid.push_back(t);
        else {
            sum1 += day13::find_reflections(grid);
            ll cnt = day13::find_smudge_reflections(grid);
            debug("Smudge reflections: %lld\n", cnt);
            sum2 += cnt;
            grid.clear();
        }
    }
    if (grid.size() > 0) {
        sum1 += day13::find_reflections(grid);
        ll cnt = day13::find_smudge_reflections(grid);
        debug("Smudge reflections: %lld\n", cnt);
        sum2 += cnt;
    }

    print_solution(1, sum1);
    print_solution(2, sum2/2);
    return 0;
}
