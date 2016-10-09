#!/bin/sh
. ./configure.sh

for PROJECT in $PROJECTS; do
  make -C $PROJECT clean
done

rm -rfv sysroot
