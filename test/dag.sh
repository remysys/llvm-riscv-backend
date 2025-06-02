#!/bin/bash

BIN="../llvm-project/build/bin"
FNAME="test42"

SRC=$FNAME.cpp
BC=$FNAME.bc
LL=$FNAME.ll
ASM=$FNAME.s

$BIN/clang $SRC -S -emit-llvm -O0 -o $LL

cat $LL
$BIN/llc -O1 -march=rriscv -fast-isel=false -view-dag-combine1-dags -view-dag-combine2-dags -view-sched-dags $LL
