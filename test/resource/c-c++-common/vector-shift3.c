





int main (int argc, char *argv[]) {
    __attribute__((vector_size((8)*sizeof(short)))) short v0 = {(short)argc,2,3,4,5,6,7};
    short sc;


    scalar1 <<= v0;

    return 0;
}
