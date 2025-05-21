float foo() {
  float a = 0.001f;
  float b = __builtin_fmaxf(a, 0.006f);
  float c = __builtin_fminf(a, 0.006f);
  return b;
}