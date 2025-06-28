#include <assert.h>
#include <stdio.h>

int x = 0;

void bar() { x++; }

void foo() {
  x++;
  bar();
}

int main() {
  foo();
  assert(x == 2);
  printf("test passed\n");
  return 0;
}