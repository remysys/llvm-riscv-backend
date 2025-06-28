#include <assert.h>
#include <stdio.h>

void foo() { int a = 0xff; }

int main() {
  foo();
  printf("test passed\n");
  return 0;
}