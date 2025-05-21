#!/bin/bash

BIN="../llvm-project/build/bin"
FNAME="test31"

SRC=$FNAME.cpp
LL=$FNAME.ll
ASM=$FNAME.s

$BIN/clang $SRC -S -emit-llvm -O0 -o $LL
cat $LL
# $BIN/llc $BC -march=rriscv --debug 
#$BIN/llc -O1 -march=rriscv -debug-only=isel  -fast-isel=false $LL
$BIN/llc -O1 -march=rriscv -debug  -fast-isel=false $LL
cat $ASM

