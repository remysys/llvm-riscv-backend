#include <assert.h>

extern int foo(int);
int main(int argc, char *argv[]) {
  int y = foo(0);
  assert(y == 2);
}