#include <assert.h>
#include <stdio.h>

int a, b, c, d, e, f;

void foo() {
  if (a > 1) {
    a += 1;
  }

  if (b >= 1) {
    b += 1;
  }

  if (c == 1) {
    c += 1;
  }

  if (d != 1) {
    d += 1;
  }

  if (e <= 1) {
    e += 1;
  }

  if (f < 1) {
    f += 1;
  }
}

int main() {
  a = 2;
  b = 2;
  c = 1;
  d = 2;
  e = 1;
  f = 0;

  foo();

  assert(a == 3);
  assert(b == 3);
  assert(c == 2);
  assert(d == 3);
  assert(e == 2);
  assert(f == 1);

  printf("test passed\n");
  return 0;
}