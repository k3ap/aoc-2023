#include <fstream>
#include <numeric>

#include "day8.hpp"
#include "../general.hpp"

int main() {
    std::ifstream ifs("day8/input");
    std::string instructions, t;
    std::getline(ifs, instructions);
    std::getline(ifs, t);

    day8::LRgraph graph = day8::parse_graph(ifs);
    print_solution(1, day8::get_num_steps(graph, instructions));

    std::vector<std::string> starting = graph.get_all_A_suffix();
    ll sol = 1;
    for (std::string s : starting) {
        sol = std::lcm(sol, (ll) day8::get_num_steps(graph, instructions, s, false));
    }
    print_solution(2, sol);

    return 0;
}
