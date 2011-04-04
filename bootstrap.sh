#!/bin/bash -x

[ ! -d ./m4 ] && mkdir ./m4

aclocal -I m4 && autoreconf -f -i -Wall,no-obsolete 

automake --add-missing

# remove some junk
rm -rf ./autom4te.cache
[ -f ./config.h.in~ ] && rm ./config.h.in~


