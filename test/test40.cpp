#include <assert.h>
#include <stdio.h>

float foo(float a, float b) { return a + b + 0.1f; }

int main() {
  float a = 1.0f;
  float b = 2.0f;
  float c = foo(a, b);
  assert((a + b + 0.1f) == c); // Check if the result matches the expected value
  printf("test passed\n");
  return 0;
}