#!/bin/bash

# NOTE: currently dynamic-modules is ONLY in emacs-25 branch
# git checkout -b emacs-25 origin/emacs-25

# install dir
INSTALL=$(pwd)/emacs

# building emacs
cd modules/emacs
./autogen.sh
# You need to set --with-modules to enable dynamic modules feature
./configure --prefix=${INSTALL} --without-x --without-ns --with-modules
make -j9 # speedup building process
make install
