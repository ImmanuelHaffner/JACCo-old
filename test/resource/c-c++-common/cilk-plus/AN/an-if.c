















extern void __assert_fail (__const char *__assertion, __const char *__file,
      unsigned int __line, __const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, __const char *__file,
      unsigned int __line,
      __const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




const int n = 8;

float x[8], y[8], z[8];

int main() {
    int i = 0;
    float x_sum =0;
    for(i=1; i<=5; i+=4 ) {
        x[0:n] = 3;
        y[0:n] = i;
        z[0:n] = 0;
        ((__sec_reduce_add(x[0:n])==3*n) ? (void) (0) : __assert_fail ("__sec_reduce_add(x[0:n])==3*n", "raw/c-c++-common/cilk-plus/AN/an-if.c", 28, __PRETTY_FUNCTION__));
        ((__sec_reduce_add(y[0:n])==i*n) ? (void) (0) : __assert_fail ("__sec_reduce_add(y[0:n])==i*n", "raw/c-c++-common/cilk-plus/AN/an-if.c", 29, __PRETTY_FUNCTION__));
        ((__sec_reduce_add(z[0:n])==0) ? (void) (0) : __assert_fail ("__sec_reduce_add(z[0:n])==0", "raw/c-c++-common/cilk-plus/AN/an-if.c", 30, __PRETTY_FUNCTION__));

        if (x[0:n] >= y[0:n]) {
            z[0:n] = x[0:n] - y[0:n];
        } else {
            z[0:n] = x[0:n] + y[0:n];
        }






        ((__sec_reduce_add(x[0:n])==3*n) ? (void) (0) : __assert_fail ("__sec_reduce_add(x[0:n])==3*n", "raw/c-c++-common/cilk-plus/AN/an-if.c", 43, __PRETTY_FUNCTION__));
        ((__sec_reduce_add(y[0:n])==i*n) ? (void) (0) : __assert_fail ("__sec_reduce_add(y[0:n])==i*n", "raw/c-c++-common/cilk-plus/AN/an-if.c", 44, __PRETTY_FUNCTION__));
        ((__sec_reduce_add(z[0:n])==(3>=i?3-i:3+i)*n) ? (void) (0) : __assert_fail ("__sec_reduce_add(z[0:n])==(3>=i?3-i:3+i)*n", "raw/c-c++-common/cilk-plus/AN/an-if.c", 45, __PRETTY_FUNCTION__));
    }
    return 0;
}
