#include <assert.h>
#include <stdio.h>

float foo(float a, float b, float c) { return a * b + c; }

int main() {
  float a = 1.0f;
  float b = 2.0f;
  float c = 3.0f;
  float result = foo(a, b, c);

  assert(result == (a * b + c));

  printf("test passed\n");
  return 0;
}