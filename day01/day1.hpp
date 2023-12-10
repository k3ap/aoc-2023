#ifndef DAY1_HPP
#define DAY1_HPP

#include <string>

#include "../general.hpp"

namespace day1 {

    const std::string numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    // Get the first and the last digit in the given string.
    std::pair<int,int> get_first_and_last_digit(const std::string& s) {
        int first=-1, last;
        for (char c : s) {
            if ('0' <= c && c <= '9') {
                if (first == -1) first = c-'0';
                last = c-'0';
            }
        }
        return {first, last};
    }

    // Get the first and the last number in the given string.
    // Numbers are digits and spelled-out numbers (one, two, ...)
    std::pair<int, int> get_first_and_last_number(const std::string& s) {

        int first=-1, last;
        for (unsigned int i = 0; i < s.length(); i++) {
            int digit = -1;

            if ('0' <= s[i] && s[i] <= '9')
                digit = s[i]-'0';

            for (int ni = 0; ni < 9; ni++) {
                if (s.find(numbers[ni], i) == i) {
                    digit = ni+1;
                    debug("Found number %s = %d\n", numbers[ni].c_str(), ni+1);
                }
            }

            if (digit == -1) continue;

            if (first == -1) first = digit;
            last = digit;
        }

        debug("First and last of %s are %d,%d\n", s.c_str(), first, last);
        return {first, last};
    }

}

#endif
