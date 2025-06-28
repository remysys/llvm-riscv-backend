#include <assert.h>
#include <stdio.h>

float bar() {
  float a = 0.001f;
  float c = __builtin_fminf(a, 0.006f);
  return a;
}

float foo() {
  float a = 0.001f;
  float b = __builtin_fmaxf(a, 0.006f);
  return b;
}

int main() {
  assert(bar() == 0.001f);
  assert(foo() == 0.006f);
  printf("test passed\n");
  return 0;
}