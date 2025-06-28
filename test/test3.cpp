#include <assert.h>
#include <stdio.h>

int x = 0;
void foo() { int l = x; }

int main() {
  foo();
  printf("test passed\n");
  return 0;
}