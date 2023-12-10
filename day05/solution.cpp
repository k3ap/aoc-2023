#include "day5.hpp"

#include <fstream>

int main() {
    std::ifstream ifs("day05/input");
    auto[rangemaps, initial_seeds] = day5::get_categories(ifs);
    ll m = -1;
    for (ll seed : initial_seeds) {
        ll end = day5::get_location_type(rangemaps, seed);
        if (m == -1 || end < m) m = end;
    }
    print_solution(1, m);

    std::vector<day5::range> ranges;
    for (unsigned int i = 0; i < initial_seeds.size(); i += 2) {
        ranges.push_back({initial_seeds[i], initial_seeds[i+1]});
    }

    std::string curr = "seed";
    while (curr != "location") {
        for (const day5::rangemap& rm : rangemaps) {
            if (rm.left != curr) continue;
            debug("Now mapping from %s to %s\n", curr.c_str(), rm.right.c_str());
            curr = rm.right;
            ranges = day5::map_intervals(rm, ranges);
        }
    }
    print_solution(2, ranges[0].start);
    return 0;
}
