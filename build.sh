#!/bin/sh
. ./configure.sh

for PROJECT in $PROJECTS; do
	make -C $PROJECT install
done
