int main (int argc, char *argv[]) {



    __attribute__((vector_size((4)*sizeof(float)))) float f0 = {1., 2., 3., 4.};
    __attribute__((vector_size((4)*sizeof(float)))) float f1, f2;

    __attribute__((vector_size((2)*sizeof(double)))) double d0 = {1., 2.};
    __attribute__((vector_size((2)*sizeof(double)))) double d1, d2;


    f1 = 2 + f0; f2 = (__attribute__((vector_size((4)*sizeof(float)))) float){2., 2., 2., 2.} + f0; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((float *) &(f1) + __i)) != (*((float *) &(f2) + __i))) __builtin_abort (); } } while (0);
    f1 = 2 - f0; f2 = (__attribute__((vector_size((4)*sizeof(float)))) float){2., 2., 2., 2.} - f0; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((float *) &(f1) + __i)) != (*((float *) &(f2) + __i))) __builtin_abort (); } } while (0);
    f1 = 2 * f0; f2 = (__attribute__((vector_size((4)*sizeof(float)))) float){2., 2., 2., 2.} * f0; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((float *) &(f1) + __i)) != (*((float *) &(f2) + __i))) __builtin_abort (); } } while (0);
    f1 = 2 / f0; f2 = (__attribute__((vector_size((4)*sizeof(float)))) float){2., 2., 2., 2.} / f0; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((float *) &(f1) + __i)) != (*((float *) &(f2) + __i))) __builtin_abort (); } } while (0);

    f1 = f0 + 2; f2 = f0 + (__attribute__((vector_size((4)*sizeof(float)))) float){2., 2., 2., 2.}; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((float *) &(f1) + __i)) != (*((float *) &(f2) + __i))) __builtin_abort (); } } while (0);
    f1 = f0 - 2; f2 = f0 - (__attribute__((vector_size((4)*sizeof(float)))) float){2., 2., 2., 2.}; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((float *) &(f1) + __i)) != (*((float *) &(f2) + __i))) __builtin_abort (); } } while (0);
    f1 = f0 * 2; f2 = f0 * (__attribute__((vector_size((4)*sizeof(float)))) float){2., 2., 2., 2.}; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((float *) &(f1) + __i)) != (*((float *) &(f2) + __i))) __builtin_abort (); } } while (0);
    f1 = f0 / 2; f2 = f0 / (__attribute__((vector_size((4)*sizeof(float)))) float){2., 2., 2., 2.}; do { int __i; for (__i = 0; __i < 4; __i++) { if ((*((float *) &(f1) + __i)) != (*((float *) &(f2) + __i))) __builtin_abort (); } } while (0);

    d1 = 2 + d0; d2 = (__attribute__((vector_size((2)*sizeof(double)))) double){2., 2.} + d0; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((double *) &(d1) + __i)) != (*((double *) &(d2) + __i))) __builtin_abort (); } } while (0);
    d1 = 2 - d0; d2 = (__attribute__((vector_size((2)*sizeof(double)))) double){2., 2.} - d0; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((double *) &(d1) + __i)) != (*((double *) &(d2) + __i))) __builtin_abort (); } } while (0);
    d1 = 2 * d0; d2 = (__attribute__((vector_size((2)*sizeof(double)))) double){2., 2.} * d0; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((double *) &(d1) + __i)) != (*((double *) &(d2) + __i))) __builtin_abort (); } } while (0);
    d1 = 2 / d0; d2 = (__attribute__((vector_size((2)*sizeof(double)))) double){2., 2.} / d0; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((double *) &(d1) + __i)) != (*((double *) &(d2) + __i))) __builtin_abort (); } } while (0);

    d1 = d0 + 2; d2 = d0 + (__attribute__((vector_size((2)*sizeof(double)))) double){2., 2.}; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((double *) &(d1) + __i)) != (*((double *) &(d2) + __i))) __builtin_abort (); } } while (0);
    d1 = d0 - 2; d2 = d0 - (__attribute__((vector_size((2)*sizeof(double)))) double){2., 2.}; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((double *) &(d1) + __i)) != (*((double *) &(d2) + __i))) __builtin_abort (); } } while (0);
    d1 = d0 * 2; d2 = d0 * (__attribute__((vector_size((2)*sizeof(double)))) double){2., 2.}; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((double *) &(d1) + __i)) != (*((double *) &(d2) + __i))) __builtin_abort (); } } while (0);
    d1 = d0 / 2; d2 = d0 / (__attribute__((vector_size((2)*sizeof(double)))) double){2., 2.}; do { int __i; for (__i = 0; __i < 2; __i++) { if ((*((double *) &(d1) + __i)) != (*((double *) &(d2) + __i))) __builtin_abort (); } } while (0);

    return 0;
}
