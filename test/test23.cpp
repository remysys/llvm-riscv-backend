#include <assert.h>
#include <stdio.h>

int bar(int a, int b) { return a + b; }

int foo() {
  int ret = bar(10, 11);
  return ret;
}

int main() {
  assert(foo() == 21);
  printf("test passed\n");
  return 0;
}