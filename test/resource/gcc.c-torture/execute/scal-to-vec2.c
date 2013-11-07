long __attribute__ ((noinline)) vlng () { return (long)42; }
int __attribute__ ((noinline)) vint () { return (int) 43; }
short __attribute__ ((noinline)) vsrt () { return (short)42; }
char __attribute__ ((noinline)) vchr () { return (char)42; }


int main (int argc, char *argv[]) {
    __attribute__((vector_size((16)*sizeof(char)))) char c0 = {argc, 1,2,3,4,5,6,7, argc, 1,2,3,4,5,6,7};
    __attribute__((vector_size((16)*sizeof(char)))) char c1;

    __attribute__((vector_size((8)*sizeof(short)))) short s0 = {argc, 1,2,3,4,5,6,7};
    __attribute__((vector_size((8)*sizeof(short)))) short s1;

    __attribute__((vector_size((4)*sizeof(int)))) int i0 = {argc, 1, 2, 3};
    __attribute__((vector_size((4)*sizeof(int)))) int i1;

    __attribute__((vector_size((2)*sizeof(long)))) long l0 = {argc, 1};
    __attribute__((vector_size((2)*sizeof(long)))) long l1;

    c1 = vchr() + c0; do { int __i; for (__i = 0; __i < 16; __i++) { if ((*((char *) &(c1) + __i)) != (vchr() + (*((char *) &(c0) + __i)))) __builtin_abort (); }} while (0);

    s1 = vsrt() + s0; do { int __i; for (__i = 0; __i < 8; __i++) { if ((*((short *) &(s1) + __i)) != (vsrt() + (*((short *) &(s0) + __i)))) __builtin_abort (); }} while (0);
    s1 = vchr() + s0; do { int __i; for (__i = 0; __i < 8; __i++) { if ((*((short *) &(s1) + __i)) != (vchr() + (*((short *) &(s0) + __i)))) __builtin_abort (); }} while (0);

    i1 = vint() * i0; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((int *) &(i1) + __i)) != (vint() * (*((int *) &(i0) + __i)))) __builtin_abort (); }} while (0);
    i1 = vsrt() * i0; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((int *) &(i1) + __i)) != (vsrt() * (*((int *) &(i0) + __i)))) __builtin_abort (); }} while (0);
    i1 = vchr() * i0; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((int *) &(i1) + __i)) != (vchr() * (*((int *) &(i0) + __i)))) __builtin_abort (); }} while (0);

    l1 = vlng() * l0; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((long *) &(l1) + __i)) != (vlng() * (*((long *) &(l0) + __i)))) __builtin_abort (); }} while (0);
    l1 = vint() * l0; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((long *) &(l1) + __i)) != (vint() * (*((long *) &(l0) + __i)))) __builtin_abort (); }} while (0);
    l1 = vsrt() * l0; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((long *) &(l1) + __i)) != (vsrt() * (*((long *) &(l0) + __i)))) __builtin_abort (); }} while (0);
    l1 = vchr() * l0; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((long *) &(l1) + __i)) != (vchr() * (*((long *) &(l0) + __i)))) __builtin_abort (); }} while (0);

    return 0;
}
