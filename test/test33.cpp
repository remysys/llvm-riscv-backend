
#include <assert.h>
#include <math.h>
#include <stdio.h>

int foo() {
  float x = 0.045;
  int ret = fabsf(x - 0.04f) < 0.001f;
  return ret;
}

int main() {
  assert(foo() == 0);
  printf("test passed\n");
  return 0;
}