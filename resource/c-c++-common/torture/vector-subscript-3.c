





typedef __attribute__((vector_size(16) )) short myvec_t;

struct vec_s {
    __attribute__((vector_size(16) )) short member;
};


int main () {
  register short __attribute__((vector_size(16) )) v0 = {1,2,3,4,5,6,7};
  register myvec_t v1 = {1,2,3,4,5,6,7};
  register struct vec_s v2;

  v2.member = v1;

  short r = v0[0] + v1[1] + v2.member[2];
  if (r != 6)
    __builtin_abort ();

  return 0;
}
