#include <assert.h>
#include <stdio.h>

int x[2];
void foo() {
  x[0] = 10;
  x[1] = 10;
  int y = x[1];
}

int main() {
  foo();
  assert(x[0] == 10);
  assert(x[1] == 10);
  printf("test passed\n");
  return 0;
}