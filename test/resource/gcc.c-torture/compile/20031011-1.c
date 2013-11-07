





typedef struct {
  int a;
  int f;
} A;

A *b;

void x (A a) {
  void y () {
    a.a = 0;
  }

  b = &a;
  y();
}
