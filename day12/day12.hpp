#ifndef DAY12_HPP
#define DAY12_HPP

#include <algorithm>
#include <map>

#include "../general.hpp"

namespace day12 {
    bool check_match(const std::vector<int> &groups, const std::string &desc) {
        std::vector<int> found_groups;
        int groupsize = 0;
        for (char c : desc) {
            switch (c) {
            case '#':
                groupsize++;
                break;
            case '.':
                if (groupsize > 0) found_groups.push_back(groupsize);
                groupsize = 0;
                break;
            }
        }
        if (groupsize > 0) found_groups.push_back(groupsize);
        return found_groups == groups;
    }

    std::string make_desc(const std::string& tmplt, int bitmask) {
        std::string desc;
        int idx = 0;
        for (char c : tmplt) {
            if (c == '?') desc += (bitmask & (1 << idx++)) ? '#' : '.';
            else desc += c;
        }
        return desc;
    }

    ll count_possibilities(const std::string& desc, const std::vector<int>& groups) {
        int num_qmarks = 0;
        for (uint i = 0; i < desc.length(); i++) {
            if (desc[i] == '?') num_qmarks++;
        }
        if (num_qmarks == 0) return (check_match(groups, desc)) ? 1 : 0;
        ll cnt = 0;
        for (int i = 0; i < (1 << num_qmarks); i++) {
            if (check_match(groups, make_desc(desc, i))) cnt++;
        }
        return cnt;
    }

    struct dp_state {
        uint desc_idx, groups_idx;

        bool operator<(const dp_state& o) const {
            if (desc_idx != o.desc_idx) return desc_idx < o.desc_idx;
            return groups_idx < o.groups_idx;
        }
    };

    ll count_possibilities_dp(const std::string& desc, const std::vector<int>& groups, dp_state state, std::map<dp_state, ll>& memo_table) {
        if (memo_table.count(state) != 0) return memo_table[state];

        debug("dp(%d,%d) called.\n", state.desc_idx, state.groups_idx);

        // border conditions
        if (state.desc_idx >= desc.size()) {
            // the next group can't start past the edge of the string
            return memo_table[state] = 0;
        }
        if (state.groups_idx >= groups.size()) {
            // the next group can't start here if there is no next group
            return memo_table[state] = 0;
        }
        if (desc.length() - state.desc_idx < groups[state.groups_idx]) {
            // we can't fit the group on the end of the string
            return memo_table[state] = 0;
        }

        // check that we actually match the desired outcome
        uint i = state.desc_idx;
        for (; i < desc.length() && i < groups[state.groups_idx] + state.desc_idx; i++) {
            if (desc[i] == '.') return memo_table[state] = 0;
        }

        // we've found a match. We now need to check a few things:
        // - if we're at the end of the string, we have succeeded if and only if
        //   this was the last group
        // - if the next character is a hash, then the group should have been
        //   longer and we've failed
        if (i >= desc.length())
            return memo_table[state] = (state.groups_idx + 1 == groups.size()) ? 1 : 0;

        if (desc[i] == '#')
            return memo_table[state] = 0;

        // if this was the last group, we just need to check that the remainder
        // doesn't contain any hashes
        if (state.groups_idx == groups.size() - 1) {
            for (; i < desc.length(); i++) {
                if (desc[i] == '#') return memo_table[state] = 0;
            }
            return memo_table[state] = 1;
        }

        // now that we've found the searched for group, we can continue scanning
        // recursively we do that by making a recursive call on every subsequent
        // index that could be the start of another group (i.e. any ? up to, and
        // including the first # we find)
        ll possibilities = 0;
        for (i++; i < desc.size() && desc[i] != '#'; i++) {
            if (desc[i] == '?') {
                debug("dp(%d,%d) calling dp(%d,%d)\n", state.desc_idx, state.groups_idx, i, state.groups_idx+1);
                possibilities += count_possibilities_dp(
                    desc, groups, {i, state.groups_idx + 1}, memo_table);
            }
        }

        // we can also start a group on a hash
        if (i < desc.size())
            possibilities += count_possibilities_dp(desc, groups, {i, state.groups_idx+1}, memo_table);

        debug("dp(%d,%d) = %lld\n", state.desc_idx, state.groups_idx, possibilities);
        return memo_table[state] = possibilities;
    }
}

#endif
