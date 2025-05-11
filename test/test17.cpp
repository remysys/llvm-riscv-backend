char a;
short b;
int c, e;

int foo(short x) {
  a = 1;
  b = a;
  c = b;
  e = c;
  return c;
}