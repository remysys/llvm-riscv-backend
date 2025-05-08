int bar(int x) {
  x += 2;
  return x + 1;
}

int foo(int x) { return bar(x) + 1; }