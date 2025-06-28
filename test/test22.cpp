#include <assert.h>
#include <stdio.h>

int bar(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int b) {
  return a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + b;
}

int foo() {
  int ret = bar(10, 11, 12, 13, 14, 15, 16, 17, 18);
  return ret;
}

int main() {
  assert(foo() == 10 + 11 + 12 + 13 + 14 + 15 + 16 + 17 + 18);
  printf("test passed\n");
  return 0;
}