#include <fstream>

#include "../general.hpp"
#include "day19.hpp"

int main() {
    std::ifstream ifs("day19/input");
    std::string t;

    bool switched = false;
    std::vector<day19::part> parts;
    std::map<std::string, day19::workflow> workflows;

    while (std::getline(ifs, t)) {
        if (t == "") {
            switched = true;
            continue;
        }

        if (switched)
            parts.push_back(day19::part(t));
        else {
            day19::workflow wf(t);
            workflows[wf.name] = wf;
        }
    }

    ll cnt = 0;
    for (auto& p : parts) {
        if (workflows["in"].accepts_part(p, workflows)) {
            debug("Accepted %lld,%lld,%lld,%lld\n", p.x, p.m, p.a, p.s);
            cnt += p.sum();
        }
    }

    print_solution(1, cnt);

    day19::partinterval everything{1, 4000, 1, 4000, 1, 4000, 1, 4000};
    print_solution(2, workflows["in"].accepts_from_interval(everything, workflows));
    return 0;
}
