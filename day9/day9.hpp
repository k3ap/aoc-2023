#ifndef DAY9_HPP
#define DAY9_HPP

#include "../general.hpp"

namespace day9 {
    std::pair<ll, ll> predict_sequence(const std::vector<ll>& seq) {
        std::vector<ll> curr[2];
        std::vector<ll> ends = {seq[seq.size()-1]};
        std::vector<ll> starts = {seq[0]};
        for (ll x : seq)
            curr[0].push_back(x);

        int p = 1;
        while (true) {
            bool allzero = true;
            for (uint i = 0; i < curr[(p + 1) % 2].size() - 1; i++) {
                curr[p].push_back(curr[(p + 1) % 2][i + 1] - curr[(p + 1) % 2][i]);
                if (curr[p][i] != 0)
                    allzero = false;
            }
            if (allzero)
                break;
            else {
                starts.push_back(curr[p][0]);
                ends.push_back(curr[p][curr[p].size()-1]);
                p++;  p %= 2;
                curr[p].clear();
            }
        }

        ll sum1 = 0;
        for (ll x : ends) sum1 += x;

        ll val2 = 0;
        for (int i = starts.size()-1; i >= 0; i--)
            val2 = starts[i] - val2;

        debug("val2: %lld\n", val2);

        return {sum1, val2};
    }
}

#endif
