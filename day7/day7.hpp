#ifndef DAY7_HPP
#define DAY7_HPP

#include <string>
#include <map>

#include "../general.hpp"

namespace day7 {
    const std::string CARDORDER = "AKQJT98765432";

    std::vector<std::vector<std::string>> possible_replacements;

    void generate_replacements() {
        possible_replacements.push_back({});
        possible_replacements.push_back({"A", "K", "Q", "T", "9", "8", "7", "6", "5", "4", "3", "2"});
        for (int len = 2; len < 6; len++) {
            std::vector<std::string> res;
            for (uint i = 0; i < CARDORDER.length(); i++) {
                if (CARDORDER[i] == 'J') continue;
                for (std::string e : possible_replacements[len-1]) {
                    res.push_back(CARDORDER[i] + e);
                }
            }
            possible_replacements.push_back(res);
        }
    }

    struct hand {
    private:
        static int get_type_of_string(std::string cards) {
            // 1 - five of a kind
            // 2 - four of a kind
            // 3 - full house
            // 4 - three of a kind
            // 5 - two pair
            // 6 - one pair
            // 7 - high card
            std::map<char, int> m;
            for (uint i = 0; i < cards.length(); i++) {
                if (m.count(cards[i]) == 0) m[cards[i]] = 1;
                else m[cards[i]]++;
            }
            if (m.size() == 1) return 1;
            if (m.size() == 4) return 6;
            if (m.size() == 5) return 7;

            for (auto[k, v] : m) {
                if (v == 4) return 2;
            }
            if (m.size() == 2) return 3;
            for (auto[k, v] : m) {
                if (v == 3) return 4;
            }
            return 5;
        }

    public:
        std::string cards;

        int get_type() const {
            return get_type_of_string(cards);
        }

        int get_best_type() const {
            // get the best type by joker replacement
            int jcnt = 0;
            for (char c : cards) {
                if (c == 'J') jcnt++;
            }
            if (jcnt == 0) return get_type();
            std::vector<std::string>& repl = possible_replacements[jcnt];
            int m = 100;
            for (std::string& r : repl) {
                std::string newcards = cards;
                int idx = 0;
                for (uint i = 0; i < newcards.size(); i++) {
                    if (newcards[i] == 'J') {
                        newcards[i] = r[idx++];
                    }
                }
                m = std::min(m, get_type_of_string(newcards));
            }
            debug("Best type of %s is %d\n", cards.c_str(), m);
            return m;
        }

        bool operator<(const hand& o) const {
            // X < Y if Y is stronger than X
            int t1 = get_type();
            int t2 = o.get_type();
            if (t1 == t2) {
                for (uint i = 0; i < cards.size(); i++) {
                    if (cards[i] != o.cards[i]) {
                        int i1 = CARDORDER.find(cards[i]);
                        int i2 = CARDORDER.find(o.cards[i]);
                        return i1 > i2;
                    }
                }
                return false;
            } else return t1 > t2;
        }
    };

    const std::string JOKERORDER = "AKQT98765432J";

    bool cmpr_joker(const std::pair<hand, int>& p1, const std::pair<hand, int>& p2) {
        const hand& o1 = p1.first;
        const hand& o2 = p2.first;
        int t1 = o1.get_best_type();
        int t2 = o2.get_best_type();
        if (t1 == t2) {
            for (uint i = 0; i < o1.cards.size(); i++) {
                if (o1.cards[i] != o2.cards[i]) {
                    int i1 = JOKERORDER.find(o1.cards[i]);
                    int i2 = JOKERORDER.find(o2.cards[i]);
                    return i1 > i2;
                }
            }
            return false;
        } else return t1 > t2;
    }
}

#endif
