DEBUG ?= 0

dnevi := day1 day2 day3 day4 day5 day6 day7 day8 day9 day10
dnevi-execs := $(foreach dan,$(dnevi),$(dan)-solution)
compile-cmd := g++ -Wall -pedantic -DDEBUG=$(DEBUG) -g


all: $(dnevi-execs)

%-solution: %/*.cpp %/*.hpp general.hpp
	$(compile-cmd) $*/solution.cpp -o $@
