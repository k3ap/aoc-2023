DEBUG ?= 0

dnevi := $(wildcard day*)
dnevi-execs := $(foreach dan,$(dnevi),solution-$(dan))
compile-cmd := g++ -Wall -pedantic -DDEBUG=$(DEBUG) -g


all: $(dnevi-execs)

solution-%: %/*.cpp %/*.hpp general.hpp
	$(compile-cmd) $*/solution.cpp -o $@
