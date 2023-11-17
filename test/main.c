#include <assert.h>

extern int x;
extern void foo(int);
int main(int argc, char *argv[]) {
  foo(0);
  assert(x == 1);
}