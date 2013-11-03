extern float sfl;
extern int sint;
extern long long sll;

int main (int argc, char *argv[]) {
    __attribute__((vector_size((8)*sizeof(short)))) short v0 = {(short)argc, 1,2,3,4,5,6,7};
    __attribute__((vector_size((8)*sizeof(short)))) short v1;

    __attribute__((vector_size((4)*sizeof(float)))) float f0 = {1., 2., 3., 4.};
    __attribute__((vector_size((4)*sizeof(float)))) float f1, f2;

    __attribute__((vector_size((4)*sizeof(int)))) int i0 = {1,2,3,4};
    __attribute__((vector_size((4)*sizeof(int)))) int i1, i2;


    int i = 12;
    double d = 3.;

    v1 = i + v0;
    v1 = 99999 + v0;

    f1 = d + f0;
    f1 = 1.3 + f0;
    f1 = sll + f0;
    f1 = ((int)998769576) + f0;


    i1 = sfl + i0;
    i1 = 1.5 + i0;
    v1 = d + v0;

    return 0;
}
