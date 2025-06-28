
#include <assert.h>
#include <stdio.h>

int bar() {
  int a = 42;   // test small immediate value
  int b = -123; // test negative immediate value
  return a + b;
}

int foo() {
  int a = 0x12345678; // test large immediate value
  int b = 0x80000000; // test 'large' negative immediate value
  return a + b;       // use these immediates in calculation
}

int main() {
  assert(bar() == -81);
  assert(foo() == 0x92345678);
  printf("test passed\n");
  return 0;
}
