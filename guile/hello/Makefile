EMACS_ROOT ?=  ../emacs
EMACS ?= emacs

CC      = gcc
LD      = gcc
LDFLAGS  = `pkg-config --libs --cflags guile-2.0`
CPPFLAGS = -I$(EMACS_ROOT)/src
CFLAGS = -std=gnu99 -ggdb3 -O2 -Wall -fPIC $(CPPFLAGS) $(LDFLAGS)


.PHONY : clean test

all: test

hello-core.so: hello-core.o
	$(LD) -L . -shared $(LDFLAGS) -o $@ $^

hello-core.o: hello-core.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	-rm -f hello-core.o hello-core.so

test: hello-core.so
	$(EMACS) -Q -batch -L . -l test/test.el -f ert-run-tests-batch-and-exit
