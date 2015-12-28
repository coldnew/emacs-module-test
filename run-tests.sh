#!/bin/sh

# We must set emacs soure directory first
export EMACS_ROOT=$(pwd)/modules/emacs
export EMACS=$(pwd)/emacs/bin/emacs

P=$(PWD)

# Test for C code
cd c && make && cd $P

# Test for C++ code
cd cpp && make && cd $P
