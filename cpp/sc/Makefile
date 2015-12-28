EMACS_ROOT ?=  ../emacs
EMACS ?= emacs

CXX      = g++
LD       = g++
CPPFLAGS = -I$(EMACS_ROOT)/src
CFLAGS = -std=c++11 -ggdb3 -O2 -Wall -fPIC $(CPPFLAGS)

.PHONY : clean test

all: test

sc-core.so: sc-core.o
	$(LD) -L . -shared $(LDFLAGS) -o $@ $^

sc-core.o: sc-core.cpp
	$(CXX) $(CFLAGS) -c -o $@ $^

clean:
	-rm -f sc-core.o sc-core.so

test: sc-core.so
	$(EMACS) -Q -batch -L . -l test/test.el -f ert-run-tests-batch-and-exit

benchmark: test
	$(EMACS) -Q -batch -L . -l test/benchmark.el
