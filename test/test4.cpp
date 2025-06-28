#include <assert.h>
#include <stdio.h>

int x = 0;
void foo() { x = 1; }

int main() {
  foo();
  assert(x == 1);
  printf("test passed\n");
  return 0;
}