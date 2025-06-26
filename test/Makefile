BIN := ../llvm-project/build/bin
FNAME := hello
OUT := $(FNAME)_rv32
SRC := $(FNAME).cpp
LL := $(FNAME).ll
ASM := $(FNAME).s
OBJ := $(FNAME).o

OBJ_S := $(FNAME)_rv32_s.o
OUT_S := $(FNAME)_rv32_s

CLANG_FLAGS := -S -emit-llvm -O0
LLC_FLAGS := -O0 -march=rriscv -fast-isel=false -debug

.PHONY: build asm dag obj clean run runs dis

build:
	cd ../llvm-project && \
	cmake -G "Unix Makefiles" -S llvm -B build -DCMAKE_BUILD_TYPE=Debug -DLLVM_ENABLE_PROJECTS="clang" -DLLVM_TARGETS_TO_BUILD="X86;RRISCV;RISCV" -DCMAKE_BUILD_TYPE="Release" -DLLVM_ENABLE_ASSERTIONS=On && \
	cd build && \
	make -j28

ir:
	$(BIN)/clang $(SRC) $(CLANG_FLAGS) -o $(LL)
	cat $(LL)

asm: ir
	$(BIN)/llc $(LLC_FLAGS) $(LL)
	cat $(ASM)

dag: ir
	$(BIN)/llc $(LLC_FLAGS) -view-dag-combine1-dags -view-dag-combine2-dags -view-sched-dags $(LL)

obj: ir
	$(BIN)/llc $(LLC_FLAGS) -filetype=obj $(LL) -o $(OBJ)
	riscv64-unknown-linux-gnu-objdump -d $(OBJ)
	riscv64-unknown-linux-gnu-readelf -r $(OBJ)

run: obj
	riscv64-unknown-linux-gnu-gcc -march=rv32g -mabi=ilp32 -static -o $(OUT) $(OBJ)
	qemu-riscv32 ./$(OUT)

objs: asm
	riscv64-unknown-linux-gnu-gcc -march=rv32g -mabi=ilp32 -c $(ASM) -o $(OBJ_S)
	riscv64-unknown-linux-gnu-objdump -d $(OBJ_S)
	riscv64-unknown-linux-gnu-readelf -r $(OBJ_S)

runs: asm
	riscv64-unknown-linux-gnu-gcc -march=rv32g -mabi=ilp32 -static -o $(OUT_S) $(ASM)
	qemu-riscv32 ./$(OUT_S)

dis:
	riscv64-unknown-linux-gnu-objdump -d $(OUT) | awk '/<main>:/,/^$$/'

clean:
	rm -f *.s *.o *.ll *.bc ./$(OUT) ./$(OUT_S)