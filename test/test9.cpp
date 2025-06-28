#include <assert.h>
#include <stdio.h>

void foo(int x, int y) { int z = x + y; }

int main() {
  foo(10, 20);
  printf("test passed\n");
  return 0;
}