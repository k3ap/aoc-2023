#ifndef DAY5_HPP
#define DAY5_HPP

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <queue>

#include "../general.hpp"

namespace day5 {

    struct range {
        ll start, length;

        ll end() const { return start + length; }

        bool operator<(const range& o) const {
            if (start == o.start) return end() < o.end();
            return start < o.start;
        }
    };

    struct rangemap {
        std::string left, right;
        std::vector<range> dest, source;

        int get_include_idx(const ll& val) const {
            for (unsigned int i = 0; i < source.size(); i++) {
                if (source[i].start <= val && val < source[i].end()) {
                    return i;
                }
            }
            return -1;
        }

        ll operator()(const ll& val) const {
            int idx = get_include_idx(val);
            debug("get_include_idx(%lld) = %d\n", val, idx);
            if (idx == -1) return val;
            else return dest[idx].start + val - source[idx].start;
        }
    };

    std::pair<std::vector<rangemap>, std::vector<ll>> get_categories(std::ifstream& ifs) {
        std::string t;
        getline(ifs, t);
        std::vector<std::string> tokens = tokenize(t, ":");
        std::vector<ll> initial_seeds;
        for (unsigned int i = 2; i < tokens.size(); i++) {
            initial_seeds.push_back(std::stoll(tokens[i]));
        }

        std::string left, right;
        std::vector<range> dest, source;

        std::vector<rangemap> rangemaps;

        while (std::getline(ifs, t)) {
            if (t.length() == 0) continue;

            tokens = tokenize(t, "-:");
            if (tokens[2] == "to") {
                if (dest.size() > 0) {
                    rangemaps.push_back({left, right, dest, source});
                    dest.clear();
                    source.clear();
                }
                left = tokens[0];
                right = tokens[4];
            } else {
                ll l = std::stoll(tokens[2]);
                range destr = {std::stoll(tokens[0]), l};
                range sourcer = {std::stoll(tokens[1]), l};
                dest.push_back(destr);
                source.push_back(sourcer);
            }
        }

        if (dest.size() > 0) {
            rangemaps.push_back({left, right, dest, source});
        }

        return {rangemaps, initial_seeds};
    }

    ll get_location_type(const std::vector<rangemap>& rangemaps, ll seed) {
        std::string curr = "seed";
        while (curr != "location") {
            for (const rangemap& rm : rangemaps) {
                if (rm.left != curr) continue;
                curr = rm.right;
                for (unsigned int i = 0; i < rm.source.size(); i++) {
                    if (rm.source[i].start <= seed && seed < rm.source[i].start + rm.source[i].length) {
                        seed = rm.dest[i].start + seed - rm.source[i].start;
                        break;
                    }
                }
            }
        }
        return seed;
    }

    // to je narobe; moral bi sprejeti samo en rangemap
    std::vector<range> map_intervals(const rangemap& rm, const std::vector<range>& ranges) {
        // 1 - enter a domain range
        // 2 - enter a source range
        // 3 - exit a source range
        // 4 - exit a domain range
        std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, std::greater<std::pair<ll, int>>> pq;

        for (const range& r : ranges) {
            pq.push({r.start, 1});
            pq.push({r.end()-1, 4});
        }
        for (unsigned int i = 0; i < rm.source.size(); i++) {
            range r = rm.source[i];
            pq.push({r.start, 2});
            pq.push({r.end()-1, 3});
        }

        ll entered = -1;
        bool active = false;

        // -1 - enter a range
        // 1 - exit a range
        std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, std::greater<std::pair<ll, int>>> res;

        while (!pq.empty()) {
            auto[pos, event] = pq.top();
            pq.pop();

            debug("Queue item: position=%lld, event=%d, entered=%lld\n", pos, event, entered);

            switch(event) {
            case 1:
                // domain entry
                if (entered != -1) throw 1;
                entered = pos;
                break;
            case 4:
                // domain exit
                if (entered > pos) {
                    entered = -1;
                    continue;
                }
                if (!active) {
                    debug("Pushing [%lld, %lld]\n", entered, pos);
                    res.push({entered, -1});
                    res.push({pos, 1});
                } else {
                    debug("Pushing [%lld, %lld]\n", rm(entered), rm(pos));
                    res.push({rm(entered), -1});
                    res.push({rm(pos), 1});
                }
                entered = -1;
                break;
            case 2:
                // source entrance
                if (entered != -1 && entered < pos) {
                    debug("Pushing [%lld, %lld]\n", entered, pos-1);
                    res.push({entered, -1});
                    res.push({pos-1, 1});
                    entered = pos;
                }
                active = true;
                break;
            case 3:
                // source exit
                if (entered != -1) {
                    debug("Pushing [%lld, %lld]\n", rm(entered), rm(pos));
                    res.push({rm(entered), -1});
                    res.push({rm(pos), 1});
                    entered = pos+1;
                }
                active = false;
            }
        }

        debug("Parsed pq events.\n");

        std::vector<range> out_ranges;
        ll start=-1;
        int d = 0;
        while (!res.empty()) {
            auto[pos, delta] = res.top();
            res.pop();
            d += delta;
            if (d == 0) {
                debug("Closing interval from %lld to %lld\n", start, pos);
                out_ranges.push_back({start, pos-start+1});
                start = -1;
            } else if (start == -1) {
                start = pos;
            }
        }

        return out_ranges;
    }
}

#endif
