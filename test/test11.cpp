#include <assert.h>
#include <stdio.h>

int foo(int x) {
  x += 2;
  return x + 1;
}

int main() {
  int result = foo(10);
  assert(result == 13);
  printf("test passed\n");
  return 0;
}