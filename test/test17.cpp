#include <assert.h>
#include <stdio.h>

char a;
short b;
int c, e;

int foo(short x) {
  a = 1;
  b = a;
  c = b;
  e = c;
  return c;
}

int main() {
  assert(foo(10) == 1);
  assert(a == 1);
  assert(b == 1);
  assert(c == 1);
  assert(e == 1);
  printf("test passed\n");
  return 0;
}