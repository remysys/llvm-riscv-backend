#include <assert.h>
#include <stdio.h>

float foo(float a, float b) { return a + b; }

int main() {
  float result = foo(1.0f, 2.0f);
  assert(result == 3.0f);
  printf("test passed\n");
  return 0;
}