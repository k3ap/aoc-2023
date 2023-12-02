DEBUG ?= 0

dnevi := day1 day2
dnevi-execs := $(foreach dan,$(dnevi),$(dan)-solution)
compile-cmd := g++ -Wall -pedantic -DDEBUG=$(DEBUG)


all: $(dnevi-execs)

%-solution: %/*.cpp %/*.hpp
	$(compile-cmd) $*/solution.cpp -o $@
