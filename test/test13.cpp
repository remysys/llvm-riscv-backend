#include <assert.h>
#include <stdio.h>

void foo() {
  int x[2];
  x[0] = 10;
  x[1] = 10;
  int y = x[0];
}

int main() {
  foo();
  printf("test passed\n");
  return 0;
}