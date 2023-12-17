DEBUG ?= 0
OPT ?= -O0

dnevi := $(wildcard day*)
dnevi-execs := $(foreach dan,$(dnevi),solution-$(dan))
compile-cmd := g++ -Wall -pedantic -DDEBUG=$(DEBUG) -g -std=c++20 $(OPT)


all: $(dnevi-execs)

solution-%: %/*.cpp %/*.hpp general.hpp
	$(compile-cmd) $*/solution.cpp -o $@
