#ifndef DAY19_HPP
#define DAY19_HPP

#include <string>
#include <utility>
#include <vector>
#include <map>

#include "../general.hpp"

namespace day19 {
    enum CompOp { less, greater };

    struct part {
        ll x, m, a, s;

        part(std::string str) {
            std::vector<std::string> tokens = tokenize(str, "", "{},xmas= \t\n");
            x = std::stoll(tokens[0]);
            m = std::stoll(tokens[1]);
            a = std::stoll(tokens[2]);
            s = std::stoll(tokens[3]);
        }

        ll sum() const {
            return x+m+a+s;
        }
    };

    struct partinterval {
        ll xmin, xmax;
        ll mmin, mmax;
        ll amin, amax;
        ll smin, smax;

        bool valid() const {
            return xmin <= xmax && mmin <= mmax && amin <= amax && smin <= smax;
        }

        ll size() const {
            return (xmax - xmin + 1) * (mmax - mmin + 1) * (amax - amin + 1) * (smax - smin + 1);
        }

        // split this interval into two, one where the condition is met
        // and another where it isn't
        std::pair<partinterval, partinterval> split(char c, CompOp op, ll value) const {
            ll activeleft, activeright;
            switch(c) {
            case 'x':
                activeleft = xmin, activeright = xmax;
                break;
            case 'm':
                activeleft = mmin, activeright = mmax;
                break;
            case 'a':
                activeleft = amin, activeright = amax;
                break;
            case 's':
                activeleft = smin, activeright = smax;
                break;
            }

            if (op == less) {
                if (activeright < value)
                    return std::make_pair(
                        partinterval{xmin, xmax, mmin, mmax, amin, amax, smin,
                                     smax},
                        partinterval{0, -1, 0, -1, 0, -1, 0, -1});

                if (value <= activeleft)
                    return std::make_pair(
                        partinterval{0, -1, 0, -1, 0, -1, 0, -1},
                        partinterval{xmin, xmax, mmin, mmax, amin, amax, smin,
                                     smax});

                switch(c) {
                case 'x':
                    return std::make_pair(partinterval{xmin, value - 1, mmin,
                                                       mmax, amin, amax, smin,
                                                       smax},
                                          partinterval{value, xmax, mmin, mmax,
                                                       amin, amax, smin, smax});
                case 'm':
                    return std::make_pair(partinterval{xmin, xmax, mmin,
                                                       value - 1, amin, amax,
                                                       smin, smax},
                                          partinterval{xmin, xmax, value, mmax,
                                                       amin, amax, smin, smax});
                case 'a':
                    return std::make_pair(
                        partinterval{xmin, xmax, mmin, mmax, amin, value - 1,
                                     smin, smax},
                        partinterval{xmin, xmax, mmin, mmax, value, amax, smin,
                                     smax});
                case 's':
                    return std::make_pair(
                        partinterval{xmin, xmax, mmin, mmax, amin, amax, smin,
                                     value - 1},
                        partinterval{xmin, xmax, mmin, mmax, amin, amax, value,
                                     smax});
                }
                throw 2;
            } else {
                if (activeright <= value)
                    return std::make_pair(
                        partinterval{0, -1, 0, -1, 0, -1, 0, -1},
                        partinterval{xmin, xmax, mmin, mmax, amin, amax, smin,
                                     smax});

                if (activeleft > value)
                    return std::make_pair(
                        partinterval{xmin, xmax, mmin, mmax, amin, amax, smin,
                                     smax},
                        partinterval{0, -1, 0, -1, 0, -1, 0, -1});

                switch(c) {
                case 'x':
                    return std::make_pair(partinterval{value + 1, xmax, mmin,
                                                       mmax, amin, amax, smin,
                                                       smax},
                                          partinterval{xmin, value, mmin, mmax,
                                                       amin, amax, smin, smax});
                case 'm':
                    return std::make_pair(partinterval{xmin, xmax, value + 1,
                                                       mmax, amin, amax, smin,
                                                       smax},
                                          partinterval{xmin, xmax, mmin, value,
                                                       amin, amax, smin, smax});
                case 'a':
                    return std::make_pair(
                        partinterval{xmin, xmax, mmin, mmax, value + 1, amax,
                                     smin, smax},
                        partinterval{xmin, xmax, mmin, mmax, amin, value, smin,
                                     smax});
                case 's':
                    return std::make_pair(
                        partinterval{xmin, xmax, mmin, mmax, amin, amax,
                                     value + 1, smax},
                        partinterval{xmin, xmax, mmin, mmax, amin, amax, smin,
                                     value});
                }
                throw 3;
            }
        }
    };

    struct rule {
        char variable;
        CompOp op;
        ll value;
        std::string result;

        rule(std::string s) {
            std::vector<std::string> tokens = tokenize(s, "<>:");
            if (tokens.size() == 1) {
                variable = 0;
                result = tokens[0];
                return;
            }
            variable = tokens[0][0];
            op = (tokens[1][0] == '<') ? less : greater;
            value = std::stoll(tokens[2]);
            result = tokens[4];
        }

        bool matches(const part& p) const {
            switch(variable) {
            case 0:
                return true;
            case 'x':
                return (op == less) ? p.x < value : p.x > value;
            case 'm':
                return (op == less) ? p.m < value : p.m > value;
            case 'a':
                return (op == less) ? p.a < value : p.a > value;
            case 's':
                return (op == less) ? p.s < value : p.s > value;
            }
            throw 1;
        }
    };

    struct workflow {
        std::string name;
        std::vector<rule> rules;

        workflow() {}

        workflow(std::string s) {
            std::vector<std::string> tokens = tokenize(s, "", "{},\n");
            name = tokens[0];
            for (uint i = 1; i < tokens.size(); i++) {
                rules.push_back(rule(tokens[i]));
            }
        }

        // whether the part is accepted at the end of the chain
        // which starts here
        bool accepts_part(const part& p, std::map<std::string, workflow>& workflows) const {
            std::string state;
            for (const rule& r : rules) {
                if (r.matches(p)) {
                    state = r.result;
                    break;
                }
            }
            if (state == "A") return true;
            if (state == "R") return false;
            return workflows[state].accepts_part(p, workflows);
        }

        ll send_over(const partinterval& interval, const std::string &result, std::map<std::string, workflow> &workflows) {
            if (result == "A") return interval.size();
            if (result == "R") return 0;
            return workflows[result].accepts_from_interval(interval, workflows);
        }

        ll accepts_from_interval(partinterval interval, std::map<std::string, workflow> &workflows) {
            ll sum = 0;
            for (const rule& r : rules) {
                if (r.variable == 0) {
                    sum += send_over(interval, r.result, workflows);
                    break;
                }
                auto[holds, doesnt] = interval.split(r.variable, r.op, r.value);
                if (holds.valid()) {
                    sum += send_over(holds, r.result, workflows);
                }
                if (!doesnt.valid()) break;
                interval = doesnt;
            }
            return sum;
        }
    };
}

#endif
