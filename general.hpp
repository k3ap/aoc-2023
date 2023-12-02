#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <vector>

typedef long long ll;

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
    return tokens;
}

#endif
