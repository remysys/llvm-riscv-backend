#include <assert.h>
#include <stdio.h>

int bar(int a, int b, int c, int d) { return a + b + c + d; }
int foo(int a, int b) {
  int ret = bar(1, 2, 3, 4);
  return ret;
}

int main() {
  assert(foo(10, 11) == 1 + 2 + 3 + 4);
  printf("test passed\n");
  return 0;
}