




int main (int argc, char *argv[]) {
    __attribute__((vector_size((4)*sizeof(float)))) float vfloat0 = {1., 2., 3., 4.};
    __attribute__((vector_size((4)*sizeof(float)))) float vfloat1 = {1., 2., 3., 4.};

    __attribute__((vector_size((4)*sizeof(int)))) int vint = {1, 1, 1, 1 };

    vint <<= vfloat0;
    vfloat0 >>= vint;

    vfloat0 <<= vfloat1;

    return 0;
}
