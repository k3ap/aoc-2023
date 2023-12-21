#include <fstream>
#include <map>
#include <numeric>

#include "day20.hpp"

day20::numsig operator+(day20::numsig x1, day20::numsig x2) {
    return {x1.first + x2.first, x1.second + x2.second};
}

int main() {
    std::ifstream ifs("day20/input");
    std::string t;
    std::map<std::string, day20::Module *> modules;
    std::map<std::string, std::vector<std::string>> connections;

    while (std::getline(ifs, t)) {
        auto [m, names] = day20::make_module(t);
        modules[names[0]] = m;
        connections[names[0]] = names;
    }

    for (auto &[name, m] : modules) {
        for (uint i = 1; i < connections[name].size(); i++) {
            if (modules.count(connections[name][i]) == 0) {
                // we're transmitting to a dud; we still need to have it there,
                // though, to count transmissions correctly
                modules[connections[name][i]] = new day20::FlipFlop();
            }
            m->connections.push_back(modules[connections[name][i]]);
        }
    }

    // part 1
    modules["broadcaster"]->initial_dfs(nullptr);

    day20::numsig num = {0, 0};
    for (int i = 0; i < 1000; i++) {
        num = num + day20::push_button(modules["broadcaster"]);
        num.first += 1;  // pulse from the button to the broadcaster
    }

    debug("%lld, %lld\n", num.first, num.second);
    print_solution(1, num.first * num.second);

    // part 2
    for (auto&[k, v] : modules)
        v->reset();

    std::vector<std::string> watched_str = {
        // "qq", "fn", "tj", "ln", "vl", "sr", "lc", "gm", "pr",
        // "vz", "qk", "sb", "pm", "cd", "hd",
        // "pl", "xm", "nn", "qj", "mc", "jz", "ch", "bp",
        // "kt", "bf", "jd", "bx", "cl", "qp", "pf", "rz"
        "xn", "qn", "xf", "zl"
    };
    std::vector<day20::Module*> watched;
    for (std::string s : watched_str) {
        watched.push_back(modules[s]);
    }

    std::vector<ll> firston(watched.size(), -1);
    std::vector<ll> on(watched.size(), -1), off(watched.size(), -1);
    std::vector<ll> intervalstart(watched.size(), -1);
    std::vector<day20::PulseStrength> prev(watched.size());

    ll cnt = 1;
    day20::push_button(modules["broadcaster"]);
    for (uint i = 0; i < watched.size(); i++) {
        day20::Module *m = watched[i];
        prev[i] = m->last_pulse;
    }

    while (off[0] == -1 || off[1] == -1 || off[2] == -2 || off[3] == -1) {
        cnt++;
        if (cnt % 10000000 == 0) debug("Got to %lld\n", cnt);
        day20::push_button(modules["broadcaster"]);
        for (uint i = 0; i < watched.size(); i++) {
            day20::Module *m = watched[i];
            if (prev[i] == day20::low && m->last_pulse == day20::high) {
                if (firston[i] == -1) {
                    firston[i] = cnt;
                    debug("wrote firston for %d\n", i);
                } else {
                    off[i] = cnt - intervalstart[i];
                    debug("wrote off for %d\n", i);
                }
                intervalstart[i] = cnt;
            } else if (prev[i] == day20::high && m->last_pulse == day20::low) {
                if (firston[i] == -1) {
                    goto out;
                }
                on[i] = cnt - intervalstart[i];
                debug("wrote on for %d\n", i);
            out:
                intervalstart[i] = cnt;
            }
            prev[i] = m->last_pulse;
        }
        // debug("After iteration %lld: ", cnt);
        // for (day20::Module* m : watched) {
        //     if (m->last_pulse == day20::high) debug2("1");
        //     else debug2("0");
        // }
        // debug2("\n");
    }
    // debug("After iteration %lld: ", cnt);
    // for (day20::Module* m : watched) {
    //     if (m->last_pulse == day20::high) debug2("1");
    //     else debug2("0");
    // }
    // debug2("\n");

    debug("i, firston, on, off:\n");
    for (uint i = 0; i < watched.size(); i++) {
        debug("%d, %lld    %lld   %lld\n", i, firston[i], on[i], off[i]);
    }

    // ll L = 1;
    // for (uint i = 0; i < watched.size(); i++) {
    //     L = std::lcm(L, on[i] + off[i]);
    //     debug("L: %lld\n", L);
    // }
    // debug("period: %lld\n", L);

    // ll N = 1;
    // while (true) {
    //     bool broken = false;
    //     for (uint i = 0; i < watched.size(); i++) {
    //         if (N < firston[i] || (N-firston[i])%(on[i]+off[i]) >= on[i]) {
    //             N += on[i]+off[i]-(N-firston[i])%(on[i]+off[i]);
    //             broken = true;
    //             break;
    //         }
    //     }
    //     if (!broken) {
    //         print_solution(2, N);
    //         break;
    //     }
    // }

    // for (uint i = 0; i < watched.size(); i++) {
    //     debug("for %lld,%lld,%lld, remainder %lld\n", firston[i], on[i], off[i], (N-firston[i])%(on[i]+off[i]));
    // }

    return 0;
}
