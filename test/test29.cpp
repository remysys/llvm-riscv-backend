
int foo() {
  float x = 0.1f;
  int ret = 0;
  if (x == 0.4f) {
    ret = 1;
  }

  if (x < 0.3f) {
    ret = 2;
  }

  if (x <= 0.2f) {
    ret = 3;
  }

  if (x > 0.5f) {
    ret = 4;
  }

  if (x >= 0.6f) {
    ret = 5;
  }

  if (x != 0.4f) {
    ret = 6;
  }

  return ret;
}