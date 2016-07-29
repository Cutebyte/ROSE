#!/bin/bash

ARCH=$(sh ./arch.sh)

#create obj catalogs
mkdir kernel_stuff/arch/$ARCH/obj
mkdir kernel_stuff/kernel/obj
mkdir bin
