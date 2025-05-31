int bar(int a, int b) { return a + b; }

int foo() {
  int ret = bar(3, 4);
  return ret;
}

int test() {
  int result = foo();
  return result;
}