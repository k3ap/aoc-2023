DEBUG ?= 0

dnevi := day1 day2 day3 day4
dnevi-execs := $(foreach dan,$(dnevi),$(dan)-solution)
compile-cmd := g++ -Wall -pedantic -DDEBUG=$(DEBUG)


all: $(dnevi-execs)

%-solution: %/*.cpp %/*.hpp general.hpp
	$(compile-cmd) $*/solution.cpp -o $@
