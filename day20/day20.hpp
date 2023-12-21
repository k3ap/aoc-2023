#ifndef DAY20_HPP
#define DAY20_HPP

#include <vector>
#include <map>

#include "../general.hpp"

#define O(idx) (((idx+1)%2))

namespace day20 {

    enum PulseStrength { low, high };

    class Module;

    class PulseRequest {
    public:
        Module* to;
        Module* from;
        PulseStrength strength;
    };

    typedef std::vector<PulseRequest>& RA;
    typedef std::pair<ll, ll> numsig;

    numsig operator+(numsig x1, numsig x2) {
        return {x1.first + x2.first, x1.second + x2.second};
    }

    class Module {
    public:
        std::vector<Module*> connections;
        bool visited = false;
        PulseStrength last_pulse = low;

        virtual void initial_dfs(Module* parent) {
            if (visited) return;
            visited = true;
            for (Module* m : connections) {
                m->initial_dfs(this);
            }
        }

        virtual numsig pulse(Module* from, PulseStrength strength, RA requests) = 0;

        virtual numsig broadcast(PulseStrength strength, RA requests) {
            last_pulse = strength;
            for (Module *m : connections) {
                requests.push_back({m, this, strength});
            }
            if (strength == low)
                return {connections.size(), 0};
            else return {0, connections.size()};
        }

        virtual void reset() {};
    };

    class FlipFlop : public Module {
    public:
        bool is_on = false;

        numsig pulse(Module* from, PulseStrength strength, RA requests) {
            if (strength == high) return {0, 0};
            is_on = !is_on;
            if (is_on) return broadcast(high, requests);
            else return broadcast(low, requests);
        }

        void reset() {
            is_on = false;
        }
    };

    class Conjunction : public Module {
    public:
        std::map<Module*, PulseStrength> inputs;

        void initial_dfs(Module* parent) {
            Module::initial_dfs(parent);
            inputs[parent] = low;
        }

        numsig pulse(Module* from, PulseStrength strength, RA requests) {
            inputs[from] = strength;
            for (auto[k, v] : inputs) {
                if (v == low) {
                    return broadcast(high, requests);
                }
            }
            return broadcast(low, requests);
        }

        void reset() {
            for (auto&[k, v] : inputs) {
                v = low;
            }
        }
    };

    class Broadcaster : public Module {
    public:
        numsig pulse(Module* from, PulseStrength strength, RA requests) {
            return broadcast(strength, requests);
        }
    };

    std::pair<Module*, std::vector<std::string>> make_module(std::string line) {
        std::vector<std::string> tokens = tokenize(line, "%&", " \t\n->,");
        if (tokens[0] == "broadcaster") {
            return {new Broadcaster(), tokens};
        }

        std::vector<std::string> rest;
        for (uint i = 1; i < tokens.size(); i++) rest.push_back(tokens[i]);
        if (tokens[0] == "%") return {new FlipFlop(), rest};
        else return {new Conjunction(), rest};
    }

    numsig push_button(Module* broadcaster) {
        std::vector<PulseRequest> requests[2];
        numsig num = broadcaster->pulse(broadcaster, low, requests[0]);
        int idx = 0;
        while (!requests[idx].empty()) {
            for (uint i = 0; i < requests[idx].size(); i++) {
                num = num + requests[idx][i].to->pulse(
                                requests[idx][i].from,
                                requests[idx][i].strength, requests[O(idx)]);
            }
            requests[idx].clear();
            idx = O(idx);
        }
        return num;
    }
}

#endif
