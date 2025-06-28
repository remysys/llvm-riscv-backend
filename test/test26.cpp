#include <assert.h>
#include <stdio.h>
typedef struct {
  int a0;
  int a1;
  int a2;
  int a3;
  int a4;
  int a5;
  int a6;
  int a7;
} X;

X bar() {
  X x;
  x.a0 = 1;
  x.a1 = 2;
  x.a7 = 3;
  return x;
}

void foo() { X x = bar(); }

int main() {
  foo();
  X x = bar();
  assert(x.a0 == 1);
  assert(x.a1 == 2);
  assert(x.a7 == 3);
  printf("test passed\n");
  return 0;
}
