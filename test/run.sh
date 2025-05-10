#!/bin/bash

BIN="../llvm-project/build/bin"
FNAME="test15"

SRC=$FNAME.cpp
BC=$FNAME.bc
LL=$FNAME.ll
ASM=$FNAME.s

$BIN/clang $SRC -c -emit-llvm -O0 -o $BC
$BIN/llvm-dis $BC
cat $LL
$BIN/llc $BC -march=rriscv --debug
cat $ASM