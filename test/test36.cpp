#include <assert.h>
#include <stdio.h>

int foo(int a, int b) { return a + b; }

int main() {
  int a = 1;
  int b = 2;
  int c = foo(a, b);
  assert((a + b) == c);
  printf("test passed\n");
  return 0;
}