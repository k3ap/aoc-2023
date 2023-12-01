#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <stdio.h>
#include <stdarg.h>

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

#endif
