#include <assert.h>
#include <stdio.h>

int bar(int x) {
  x += 2;
  return x + 1;
}

int foo(int x) { return bar(x) + 1; }

int main() {
  int result = foo(10);
  assert(result == 14);
  printf("test passed\n");
  return 0;
}