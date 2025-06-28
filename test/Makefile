BIN := ../llvm-project/build/bin
FNAME := test0
OUT := $(FNAME)_rv32
SRC := $(FNAME).cpp
LL := $(FNAME).ll
ASM := $(FNAME).s
OBJ := $(FNAME).o

OBJ_S := $(FNAME)_rv32_s.o
OUT_S := $(FNAME)_rv32_s

CLANG_FLAGS := -S -emit-llvm -O0
LLC_FLAGS := -O0 -march=rriscv -fast-isel=false
LLC_FLAGS_DEBUG := -O0 -march=rriscv -fast-isel=false -debug

TESTS := $(basename $(wildcard test*.cpp))
TEST_BINS := $(addsuffix _rv32, $(TESTS))

.PHONY: build ir asm dag obj run objs runs dis clean test

build:
	cd ../llvm-project && \
	cmake -G "Unix Makefiles" -S llvm -B build -DCMAKE_BUILD_TYPE=Debug -DLLVM_ENABLE_PROJECTS="clang" -DLLVM_TARGETS_TO_BUILD="X86;RRISCV;RISCV" -DCMAKE_BUILD_TYPE="Release" -DLLVM_ENABLE_ASSERTIONS=On && \
	cd build && \
	make -j28 clang llc

$(LL): $(SRC)
	$(BIN)/clang $(SRC) $(CLANG_FLAGS) -o $(LL)

$(ASM): $(LL)
	$(BIN)/llc $(LLC_FLAGS) $(LL) -o $(ASM)

$(OBJ): $(LL)
	$(BIN)/llc $(LLC_FLAGS) -filetype=obj $(LL) -o $(OBJ)

$(OBJ_S): $(ASM)
	riscv64-unknown-linux-gnu-gcc -march=rv32g -mabi=ilp32d -c $(ASM) -o $(OBJ_S)

$(OUT): $(OBJ)
	riscv64-unknown-linux-gnu-gcc -march=rv32g -mabi=ilp32d -static -o $(OUT) $(OBJ)

$(OUT_S): $(ASM)
	riscv64-unknown-linux-gnu-gcc -march=rv32g -mabi=ilp32d -static -o $(OUT_S) $(ASM)

ir: $(LL)
	cat $(LL)

asm: $(ASM)
	cat $(ASM)

dag: $(LL)
	$(BIN)/llc $(LLC_FLAGS) -view-dag-combine1-dags -view-dag-combine2-dags -view-sched-dags $(LL)

obj: $(OBJ)
	riscv64-unknown-linux-gnu-objdump -d $(OBJ)
	riscv64-unknown-linux-gnu-readelf -r $(OBJ)

run: $(OUT)
	qemu-riscv32 ./$(OUT)

objs: $(OBJ_S)
	riscv64-unknown-linux-gnu-objdump -d $(OBJ_S)
	riscv64-unknown-linux-gnu-readelf -r $(OBJ_S)

runs: $(OUT_S)
	qemu-riscv32 ./$(OUT_S)

dis:
	riscv64-unknown-linux-gnu-objdump -d $(OUT) | awk '/<main>:/,/^$$/'


%_rv32.ll: %.cpp
	$(BIN)/clang $< $(CLANG_FLAGS) -o $@

%_rv32.o: %_rv32.ll
	$(BIN)/llc $(LLC_FLAGS) -filetype=obj $< -o $@

%_rv32: %_rv32.o
	riscv64-unknown-linux-gnu-gcc -march=rv32g -mabi=ilp32d -static -o $@ $<

test: $(TEST_BINS)
	@for bin in $(shell echo $(TEST_BINS) | tr ' ' '\n' | sort -V); do \
		echo "running $$bin ..."; \
		qemu-riscv32 ./$$bin || exit 1; \
	done

clean:
	rm -f *.s *.o *.ll *.bc ./$(OUT) ./$(OUT_S) $(TEST_BINS)

