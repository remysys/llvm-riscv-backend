int bar(int a, int b) { return a + b; }

int foo() {
  int ret = bar(10, 11);
  return ret;
}