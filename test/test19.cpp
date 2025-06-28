#include <assert.h>
#include <stdio.h>

int bar(int a, int b, int c) { return 1; }
int foo(int a, int b) {
  int ret = bar(1, 2, 3);
  return 1;
}

int main() {
  assert(foo(10, 11) == 1);
  printf("test passed\n");
  return 0;
}