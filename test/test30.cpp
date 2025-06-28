#include <assert.h>
#include <math.h>
#include <stdio.h>

float foo(float a, double b) { return a + b; }

int main() {
  double result = foo(1.0f, 2.0);
  assert(fabs(result - 3.0) < 1e-6);
  printf("test passed\n");
  return 0;
}