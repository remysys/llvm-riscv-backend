#include <assert.h>

extern int x;
extern void foo();
int main(int argc, char *argv[]) {
  foo();
  assert(x == 2);
}