#!/bin/bash -x

aclocal && autoreconf -f -i -Wall,no-obsolete 

automake --add-missing

# remove some junk
rm -rf ./autom4te.cache
rm ./config.h.in~


