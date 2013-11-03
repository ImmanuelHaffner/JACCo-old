typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
int failures;

struct S1
{
  _Decimal64 a[0];
};

struct S2
{
  struct
  {
    _Decimal64 e;
  } b[0];
};

struct S3
{
  union
  {
    _Decimal64 c;
  } a[0];
};

struct S4
{
  int a[0];
  _Decimal64 b[0];
};

struct S5
{
  union
  {
    _Decimal64 c[0];
  } a;
};

int check_var (int z, ...)
{
  long long result;
  va_list ap;
  __builtin_va_start(ap,z);
  __builtin_va_arg(ap,struct S1);
  result = __builtin_va_arg(ap,long long);
  __builtin_va_end(ap);

  return (result == 2LL);
}

int main ()
{
  struct S1 s1;
  struct S2 s2;
  struct S3 s3;
  struct S4 s4;
  struct S5 s5;

  if (check_var (2, s1, 2LL) == 0)
    __builtin_abort ();;
  if (check_var (2, s2, 2LL) == 0)
    __builtin_abort ();;
  if (check_var (2, s3, 2LL) == 0)
    __builtin_abort ();;
  if (check_var (2, s4, 2LL) == 0)
    __builtin_abort ();;
  if (check_var (2, s5, 2LL) == 0)
    __builtin_abort ();;

  return 0;
}
