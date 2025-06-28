#include <assert.h>
#include <stdio.h>

void foo() {
  int x = 1;
  int y = x;
  int z = y;
  return;
}

int main() {
  foo();
  printf("test passed\n");
  return 0;
}