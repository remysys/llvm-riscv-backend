/*
 * riscv64-unknown-linux-gnu-gcc -march=rv32g -mabi=ilp32 -static hello.cpp -o
 * hello qemu-riscv32 ./hello
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Hello, RISC-V!\n");
  return 0;
}
