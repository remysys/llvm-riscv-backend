BIN := ../llvm-project/build/bin
FNAME := test41
SRC := $(FNAME).cpp
LL := $(FNAME).ll
ASM := $(FNAME).s
OBJ := $(FNAME).o

CLANG_FLAGS := -S -emit-llvm -O0
LLC_FLAGS := -O0 -march=rriscv -fast-isel=false

.PHONY: build asm dag obj clean

.PHONY: build asm dag obj clean

build:
	cd ../llvm-project && \
	cmake -G "Unix Makefiles" -S llvm -B build -DCMAKE_BUILD_TYPE=Debug -DLLVM_ENABLE_PROJECTS="clang" -DLLVM_TARGETS_TO_BUILD="X86;RRISCV;RISCV" -DCMAKE_BUILD_TYPE="Release" -DLLVM_ENABLE_ASSERTIONS=On && \
	cd build && \
	make -j $(nproc)

asm:
	$(BIN)/clang $(SRC) $(CLANG_FLAGS) -o $(LL)
	cat $(LL)
	$(BIN)/llc $(LLC_FLAGS) -debug $(LL)
	cat $(ASM)

dag:
	$(BIN)/clang $(SRC) $(CLANG_FLAGS) -o $(LL)
	cat $(LL)
	$(BIN)/llc $(LLC_FLAGS) -view-dag-combine1-dags -view-dag-combine2-dags -view-sched-dags $(LL)

obj:
	$(BIN)/clang $(SRC) $(CLANG_FLAGS) -o $(LL)
	$(BIN)/llc $(LLC_FLAGS) -filetype=obj $(LL) -o $(OBJ)
	riscv64-unknown-linux-gnu-objdump -d $(OBJ)
	riscv64-unknown-linux-gnu-readelf -r $(OBJ) 

clean:
	rm -f *.s *.o *.ll *.bc
	rm -rf ../llvm-project/build