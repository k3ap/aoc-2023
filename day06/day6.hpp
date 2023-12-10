#ifndef DAY6_HPP
#define DAY6_HPP

#include "../general.hpp"

namespace day6 {
    ll ways_to_break_record(ll time, ll record_distance) {
        ll cnt = 0;
        for (int i = 0; i < time; i++) {
            ll dist = (time-i) * i;
            if (dist > record_distance) cnt++;
        }
        return cnt;
    }
}

#endif
