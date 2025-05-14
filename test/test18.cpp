int bar(int a, int b, int c, int d) { return a + b + c + d; }

int foo() {
  int ret = bar(1, 2, 3, 4);
  return ret;
}