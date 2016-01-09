#!/bin/sh

# We must set emacs soure directory first
export EMACS_ROOT=$(pwd)/modules/emacs
export EMACS=$(pwd)/emacs/bin/emacs

P=$(pwd)

# Test for C code
(cd c && make)

# Test for C++ code
(cd cpp && make)

# Test for Guile
(cd guile && make)
