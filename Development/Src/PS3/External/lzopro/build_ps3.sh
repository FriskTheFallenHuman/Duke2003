#! /bin/sh
# vi:ts=4:et
set -e
echo "// Using GNU C compiler."
echo "//"

test "X${top_srcdir}" = X && top_srcdir=`echo "$0" | sed 's,[^/]*$,,'`../../../../External/lzopro

CC="ppu-lv2-gcc"
AR="ppu-lv2-ar"
ARFLAGS="r"
CFLAGS="-Wall -Wno-uninitialized -O2 -fomit-frame-pointer"

. $top_srcdir/B/generic/build.sh
