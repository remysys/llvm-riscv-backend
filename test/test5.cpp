#include <assert.h>
#include <stdio.h>

void foo() {
  int x = 1;
  return;
}
int main() {
  foo();
  printf("test passed\n");
  return 0;
}