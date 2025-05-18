typedef struct {
  int a0;
  int a1;
  int a2;
  int a7;
} X;

X bar() {
  X x;
  x.a0 = 1;
  x.a1 = 2;
  x.a7 = 3;
  return x;
}

void foo() { X x = bar(); }
