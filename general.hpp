#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <vector>
#include <map>

typedef long long ll;
typedef unsigned int uint;

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

enum Direction { north='N', south='S', west='W', east='E' };

std::vector<Direction> get_normal(Direction dir) {
    if (dir == north || dir == south) return {east, west};
    else return {north, south};
}

Direction get_opposite(Direction dir) {
    switch (dir) {
    case north:
        return south;
    case south:
        return north;
    case west:
        return east;
    case east:
        return west;
    }
    return north;
}

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
        switch (dir) {
        case north:
            return i > 0;
        case south:
            return i < ilim - 1;
        case west:
            return j > 0;
        case east:
            return j < jlim - 1;
        }
        return false;
    }
};

#define AT(c) [(c.i)][(c.j)]

struct c2 {
    ll x, y;

    bool operator<(const c2 &o) const {
        if (x == o.x) return y < o.y;
        return x < o.x;
    }

    bool operator==(const c2 &o) const { return x == o.x && y == o.y; }

    bool operator!=(const c2 &o) const { return x != o.x || y != o.y; }

    c2 operator-(const c2& o) const { return {x - o.x, y  - o.y};}

    int manhattan(const c2 &o) const {
        return std::abs(x - o.x) + std::abs(y - o.y);
    }

    std::vector<c2> adjacent4() {
        std::vector<c2> res;
        res.push_back({x - 1, y});
        res.push_back({x, y - 1});
        res.push_back({x + 1, y});
        res.push_back({x, y + 1});
        return res;
    }

    c2 follow(Direction dir, int len=1) {
        switch(dir) {
        case north:
            return {x, y-len};
        case south:
            return {x, y+len};
        case west:
            return {x-len, y};
        case east:
            return {x+len, y};
        }
        return {ILIM, JLIM};
    }

    ll cross(const c2& o) {
        return x * o.y - y * o.x;
    }
};

template<typename atomT>
struct offsetgrid {
    std::map<c2, atomT> underlying;
    atomT defaultvalue;

    offsetgrid(atomT defaultvalue) : underlying(), defaultvalue(defaultvalue) {}

    atomT at(c2 c) const {
        if (!underlying.contains(c)) return defaultvalue;
        return underlying[c];
    }

    atomT at(ll x, ll y) const {
        if (!underlying.contains({x, y})) return defaultvalue;
        return underlying[{x, y}];
    }

    void set(c2 c, atomT atom) {
        underlying[c] = atom;
    }

    void set(ll x, ll y, atomT atom) {
        underlying[{x, y}] = atom;
    }

    std::vector<std::vector<atomT>> get_grid() const {
        ll minleft = 0, maxright = 0, mindown = 0, maxup = 0;
        for (auto [k, v] : underlying) {
            minleft = std::min(minleft, k.x);
            maxright = std::max(maxright, k.x);
            mindown = std::min(mindown, k.y);
            maxup = std::max(maxup, k.y);
        }
        std::vector<atomT> dv;
        for (int i = minleft; i <= maxright; i++) dv.push_back(defaultvalue);
        std::vector<std::vector<atomT>> out(maxup - mindown + 1, dv);
        for (auto [k, v] : underlying) {
            out[k.y - mindown][k.x - minleft] = v;
        }
        return out;
    }
};

void debug_draw_offsetgrid(const offsetgrid<char> &grid) {
#if DEBUG
    std::vector<std::vector<char>> vvc = grid.get_grid();
    std::vector<std::string> out;
    for (uint i = 0; i < vvc.size(); i++) {
        std::string row = "";
        for (char c : vvc[i]) row += c;
        out.push_back(row);
    }
    for (uint i = 0; i < out.size(); i++) {
        debug("%s\n", out[i].c_str());
    }
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
