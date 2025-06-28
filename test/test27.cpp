#include <assert.h>
#include <stdio.h>

float foo(float a, float b) { return a + b + (double)0.1; }

int main() {
  float result = foo(1.0f, 2.0f);
  assert(result == 3.1f);
  printf("test passed\n");
  return 0;
}