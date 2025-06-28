#include <assert.h>
#include <stdio.h>

int bar() { return 1; }
int foo() { return bar(); }

int main() {
  assert(foo() == 1);
  printf("test passed\n");
  return 0;
}