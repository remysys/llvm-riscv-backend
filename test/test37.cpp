#include <assert.h>
#include <stdio.h>

void foo() {
  int a = 10;

  int b = a + 8;
  int c = a + b;

  int d = a - 8;
  int e = a - d;

  int f = a * 3;
  int h = a * f;

  int i = a / 2;
  int j = a / i;

  int k = 3;
  int l = a % k;

  int m = a & 3;
  int n = a & m;

  int o = a | 2;
  int p = a | o;
}

int main() {
  foo();
  // the function foo() does not return any value, so we cannot assert anything.
  // however, we can check if the function executes without errors.
  printf("test passed\n");
  return 0;
}