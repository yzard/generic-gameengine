#!/bin/bash -x

aclocal && autoreconf -f -i -Wall,no-obsolete 
[ -d ./autom4te.cache ] && rm -rf ./autom4te.cache

automake --add-missing
