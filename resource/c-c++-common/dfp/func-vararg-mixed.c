



typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
int failures;




static _Decimal32
vararg_d32 (unsigned arg, ...)
{
  va_list ap;
  _Decimal32 result;

  __builtin_va_start(ap,arg);

  __builtin_va_arg(ap,unsigned int);
  __builtin_va_arg(ap,_Decimal128);
  __builtin_va_arg(ap,double);
  result = __builtin_va_arg(ap,_Decimal32);

  __builtin_va_end(ap);
  return result;
}

static _Decimal32
vararg_d64 (unsigned arg, ...)
{
  va_list ap;
  _Decimal64 result;

  __builtin_va_start(ap,arg);

  __builtin_va_arg(ap,unsigned int);
  __builtin_va_arg(ap,_Decimal128);
  __builtin_va_arg(ap,double);
  __builtin_va_arg(ap,_Decimal32);
  result = __builtin_va_arg(ap,_Decimal64);

  __builtin_va_end(ap);
  return result;
}

static _Decimal128
vararg_d128 (unsigned arg, ...)
{
  va_list ap;
  _Decimal128 result;

  __builtin_va_start(ap,arg);

  __builtin_va_arg(ap,unsigned int);
  result = __builtin_va_arg(ap,_Decimal128);

  __builtin_va_end(ap);
  return result;
}

static unsigned int
vararg_int (unsigned arg, ...)
{
  va_list ap;
  unsigned int result;

  __builtin_va_start(ap,arg);

  result = __builtin_va_arg(ap,unsigned int);

  __builtin_va_end(ap);
  return result;
}

static double
vararg_double (unsigned arg, ...)
{
  va_list ap;
  float result;

  __builtin_va_start(ap,arg);

  __builtin_va_arg(ap,unsigned int);
  __builtin_va_arg(ap,_Decimal128);
  result = __builtin_va_arg(ap,double);

  __builtin_va_end(ap);
  return result;
}


int
main ()
{
  if (vararg_d32 (3, 0, 1.0dl, 2.0, 3.0df, 4.0dd) != 3.0df) __builtin_abort ();
  if (vararg_d64 (4, 0, 1.0dl, 2.0, 3.0df, 4.0dd) != 4.0dd) __builtin_abort ();
  if (vararg_d128 (1, 0, 1.0dl, 2.0, 3.0df, 4.0dd) != 1.0dl) __builtin_abort ();
  if (vararg_int (0, 0, 1.0dl, 2.0, 3.0df, 4.0dd) != 0) __builtin_abort ();
  if (vararg_double (2, 0, 1.0dl, 2.0, 3.0df, 4.0dd) != 2.0) __builtin_abort ();

  return 0;
}
