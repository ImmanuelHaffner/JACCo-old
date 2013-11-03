

typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
int failures;

struct S1
{
  struct
  {
    _Decimal64 e;
  } b[0];
};



int check_var(int z,...)
{
  double d;
  struct S1 s1;
  long long result;
  va_list ap;
  __builtin_va_start(ap,z);
  d = __builtin_va_arg(ap,double);
  s1 = __builtin_va_arg(ap,struct S1);
  result = __builtin_va_arg(ap,long long);
  __builtin_va_end(ap);
  return (result == 2LL);

}

int
main ()
{
  struct S1 s1;
  struct S1 a1[5];

  if (check_var(5, 1.0, s1, 2LL, a1[2], a1[2]) == 0)
    __builtin_abort ();

  return 0;
}
