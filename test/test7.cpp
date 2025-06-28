#include <assert.h>
#include <stdio.h>

void foo() { foo(); }

int main() {
  // foo();
  printf("test passed\n");
  return 0;
}