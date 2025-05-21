
int foo() {
  double x = 0.1;
  int ret = 0;
  if (x == 0.4) {
    ret = 1;
  }

  if (x < 0.3) {
    ret = 2;
  }

  if (x <= 0.2) {
    ret = 3;
  }

  if (x > 0.5) {
    ret = 4;
  }

  if (x >= 0.6) {
    ret = 5;
  }

  if (x != 0.4) {
    ret = 6;
  }

  return ret;
}