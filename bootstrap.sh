#!/bin/bash -x

[ -d ./autom4te.cache ] && rm -rf ./autom4te.cache

aclocal && autoreconf -f -i -Wall,no-obsolete 
automake --add-missing
