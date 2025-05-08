#!/bin/bash

pushd ../llvm-project/
cmake -G "Unix Makefiles" -S llvm -B build -DCMAKE_BUILD_TYPE=Debug -DLLVM_ENABLE_PROJECTS="clang" -DLLVM_TARGETS_TO_BUILD="X86;RRISCV;RISCV" -DCMAKE_BUILD_TYPE="Release" -DLLVM_ENABLE_ASSERTIONS=On

pushd build
make -j ${nproc}
popd
popd