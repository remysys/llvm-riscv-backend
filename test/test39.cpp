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
  a = 0;
  b = 0;
  c = 0;
  d = 0;
  e = 0;
  f = 0;

  foo();

  assert(a == 0);
  assert(b == 0);
  assert(c == 0);
  assert(d == 1);
  assert(e == 1);
  assert(f == 1);
  printf("test passed\n");
  return 0; // Test passed
}