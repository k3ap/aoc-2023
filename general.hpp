#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <vector>

typedef long long ll;
typedef unsigned int uint;

enum Direction { north='N', south='S', west='W', east='E' };

const uint ILIM = 1000000000, JLIM = 1000000000;

// grid coordinate
struct cg {
    uint i, j;

    bool operator<(const cg &o) const {
        if (i == o.i) return j < o.j;
        return i < o.i;
    }

    bool operator==(const cg &o) const { return i == o.i && j == o.j; }

    bool operator!=(const cg &o) const { return i != o.i || j != o.j; }

    uint manhattan(const cg &o) const {
        uint d1 = (i < o.i) ? o.i - i : i - o.i;
        uint d2 = (j < o.j) ? o.j - j : j - o.j;
        return d1 + d2;
    }

    std::vector<cg> adjacent4(uint ilim = ILIM, uint jlim = 1000000000) {
        std::vector<cg> res;
        if (i > 0) res.push_back({i - 1, j});
        if (j > 0) res.push_back({i, j - 1});
        if (i < ilim - 1) res.push_back({i + 1, j});
        if (j < jlim - 1) res.push_back({i, j + 1});
        return res;
    }

    cg follow(Direction dir) {
        switch(dir) {
        case north:
            return {i-1, j};
        case south:
            return {i+1, j};
        case west:
            return {i, j-1};
        case east:
            return {i, j+1};
        }
        return {ILIM, JLIM};
    }

    bool can_follow(Direction dir, uint ilim = ILIM, uint jlim = JLIM) {
        switch(dir) {
        case north:
            return i > 0;
        case south:
            return i < ilim-1;
        case west:
            return j > 0;
        case east:
            return j < jlim-1;
        }
        return false;
    }
};

#define AT(c) [(c.i)][(c.j)]

void print_solution(int part, ll solution) {
    printf("\033[44m Solution for part %d:\033[0m %lld\n", part, solution);
}

void debug(const char* format, ...) {
#if DEBUG
    printf("\033[41m DEBUG \033[0m");

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}

void debug2(const char* format, ...) {
#if DEBUG
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
#endif
}

/*
 * Split a string into tokens by delimiters and special characters.
 * Special characters will always be placed in a token by themselves, delimiters will
 * split different tokens, but will not be included in any.
 */
std::vector<std::string> tokenize(const std::string& s, const std::string special="", const std::string delimiters=" \t\n") {
    std::vector<std::string> tokens;
    std::string token;
    for (char c : s) {
        if (special.find(c) != std::string::npos) {
            // This is a special character
            if (token.length() > 0) tokens.push_back(token);
            tokens.push_back(std::string(1, c));
            token = "";
        } else if (delimiters.find(c) != std::string::npos) {
            if (token.length() > 0) tokens.push_back(token);
            token = "";
        } else {
            token += c;
        }
    }
    if (token.length() > 0) tokens.push_back(token);
    return tokens;
}

#endif
