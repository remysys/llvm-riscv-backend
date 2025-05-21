
#include <math.h>
int foo() {
  float x = 0.045;
  int ret = fabsf(x - 0.04f) < 0.001f;
  return ret;
}