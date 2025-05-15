int bar(int a, int b, int c) { return 1; }
int foo(int a, int b) {
  int ret = bar(1, 2, 3);
  return 1;
}