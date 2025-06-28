#include <assert.h>
#include <stdio.h>

int x = 0;
void bar(int a) { x += a; }
void foo(int a) { bar(a + 1); }

int main() {
  foo(10);
  assert(x == 11);
  printf("test passed\n");
  return 0;
}