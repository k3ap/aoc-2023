#include "../general.hpp"
#include "day2.hpp"

#include <fstream>
#include <string>

int main() {
    std::ifstream ifs("day2/input");
    std::string s;
    int sum = 0;
    int powersum = 0;
    while (getline(ifs, s)) {
        day2::game g = day2::parse_game(s);

        int m_red = 0, m_blue = 0, m_green = 0;
        for (unsigned int i = 0; i < g.red_seq.size(); i++) {
            m_red = std::max(m_red, g.red_seq[i]);
            m_blue = std::max(m_blue, g.blue_seq[i]);
            m_green = std::max(m_green, g.green_seq[i]);
        }
        powersum += m_red * m_blue * m_green;
        if (m_red <= 12 && m_blue <= 14 && m_green <= 13) {
            sum += g.gameid;
        }
        else debug("Game %d FAILS with m_red=%d, m_blue=%d, m_green=%d\n", g.gameid, m_red, m_blue, m_green);
    }
    print_solution(1, sum);
    print_solution(2, powersum);
    return 0;
}
