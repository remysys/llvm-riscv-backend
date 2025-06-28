#include <assert.h>
#include <stdio.h>

int a, b, c, d, e, f;

void foo() {
  int x = 0;
  a = x > 10;
  b = x < 10;
  c = x == 10;
  d = x != 10;
  e = (x >= 10);
  f = (x <= 10);
}

int main() {

  foo();

  assert(a == 0);
  assert(b == 1);
  assert(c == 0);
  assert(d == 1);
  assert(e == 0);
  assert(f == 1);

  printf("test passed\n");
  return 0;
}