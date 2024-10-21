llvm-riscv-backend
===

learn LLVM by creating a RISC-V backend step by step

## build
build rrisc-v target, ensuring LLVM_TARGETS_TO_BUILD includes RRISCV
```
cd llvm-project/
cmake -G "Unix Makefiles" -S llvm -B build -DLLVM_ENABLE_PROJECTS="clang" -DLLVM_TARGETS_TO_BUILD="X86;RRISCV;RISCV" -DCMAKE_BUILD_TYPE="Release" -DLLVM_ENABLE_ASSERTIONS=On
cd build && make -j$(nproc)
```

check rrisc-v target build success, a new rriscv backend will be available
```
./bin/llc --version
Registered Targets:
    ...
    rriscv  - Remy's RISC-V backend
```

## run examples

run test examples on the rrisc-v target. 
compiling test examples to LLVM BitCode and IR
```
./bin/clang ../../test/test.c -c -emit-llvm -O0 -o test.bc
./bin/llvm-dis test.bc
cat test.ll
```
run IR with llc using the rrisc-v target

```
./bin/llc test.bc -march=rriscv
```

view more runtime information:
```
./bin/llc test.ll -march=rriscv --debug
./bin/llc test.ll -march=rriscv --debug -o -
```
