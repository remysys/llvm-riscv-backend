BIN := ../llvm-project/build/bin
FNAME := test36
SRC := $(FNAME).cpp
LL := $(FNAME).ll
ASM := $(FNAME).s
OBJ := $(FNAME).o

.PHONY: build asm dag obj clean

build:
	cd ../llvm-project && \
	cmake -G "Unix Makefiles" -S llvm -B build -DCMAKE_BUILD_TYPE=Debug -DLLVM_ENABLE_PROJECTS="clang" -DLLVM_TARGETS_TO_BUILD="X86;RRISCV;RISCV" -DCMAKE_BUILD_TYPE="Release" -DLLVM_ENABLE_ASSERTIONS=On && \
	cd build && \
	make -j $(nproc)

asm:
	$(BIN)/clang $(SRC) -S -emit-llvm -O0 -o $(LL)
	cat $(LL)
	$(BIN)/llc -O1 -march=rriscv -debug -fast-isel=false $(LL)
	cat $(ASM)

dag:
	$(BIN)/clang $(SRC) -S -emit-llvm -O0 -o $(LL)
	cat $(LL)
	$(BIN)/llc -O1 -march=rriscv -fast-isel=false -view-dag-combine1-dags -view-dag-combine2-dags -view-sched-dags $(LL)

obj:
	$(BIN)/clang $(SRC) -S -emit-llvm -O0 -o $(LL)
	$(BIN)/llc -O1 -march=rriscv -filetype=obj $(LL) -o $(OBJ)
	riscv64-unknown-linux-gnu-objdump -d $(OBJ) 

clean:
	rm -f *.s *.o *.ll *.bc
	rm -rf ../llvm-project/build