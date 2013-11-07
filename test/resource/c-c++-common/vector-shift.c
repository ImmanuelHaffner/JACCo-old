




int main (int argc, char *argv[]) {
    __attribute__((vector_size((4)*sizeof(char)))) char vchar = {1,2,3,4};
    __attribute__((vector_size((4)*sizeof(int)))) int vint = {1,1,1,1};

    vint <<= vchar;
    vchar >>= vint;

    return 0;
}
