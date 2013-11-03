


int main (int argc, char *argv[]) {
  __attribute__((vector_size(8*sizeof(short)))) short v0 = {argc,2,3,4,5,6,7};
  __attribute__((vector_size(8*sizeof(short)))) short v1 = {2,2,2,2,2,2,2};
  __attribute__((vector_size(8*sizeof(short)))) short r1,r2,r3,r4;
  int i = 8;

  r1 = v0 << 1;
  r2 = v0 >> 1;

  r3 = v0 << v1;
  r4 = v0 >> v1;

  return 0;
}
