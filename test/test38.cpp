#include <assert.h>
#include <stdio.h>

int bar(int a, int b) { return a + b; }

int foo() {
  int ret = bar(3, 4);
  return ret;
}

int main() {
  assert(foo() == 7); // Check if the result matches the expected value
  printf("test passed\n");
  return 0;
}