
#include <assert.h>
#include <math.h>
#include <stdio.h>

float foo(float a, double b) {
  float x = a + b;
  float y = x * 0.1f;
  float z = y / 2.0f;
  float k = z * 2.0f;
  double l = x;
  double m = l * 0.1;
  double n = m / 2.0;
  double t = n * 2.0;
  return t;
}

int main() {
  float result = foo(1.0f, 2.0);
  assert(fabs(result - 0.3) < 1e-6);
  printf("test passed\n");
  return 0;
}