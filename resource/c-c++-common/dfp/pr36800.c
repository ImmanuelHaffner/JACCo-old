

typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
int failures;

void
f (int a, ...)
{
  va_list ap;
  if (a != 0)
    __builtin_abort ();
  __builtin_va_start(ap,a);
  if (__builtin_va_arg(ap,_Decimal128) != 1.2DL)
    __builtin_abort ();
  if (__builtin_va_arg(ap,_Decimal128) != 2.34DL)
    __builtin_abort ();
  if (__builtin_va_arg(ap,_Decimal128) != 3.456DL)
    __builtin_abort ();
  if (__builtin_va_arg(ap,_Decimal128) != 4.567DL)
    __builtin_abort ();
  if (__builtin_va_arg(ap,double) != 5.125)
    __builtin_abort ();
  __builtin_va_end(ap);
}

int
main (void)
{
  f (0, 1.2DL, 2.34DL, 3.456DL, 4.567DL, 5.125);

  return 0;
}
