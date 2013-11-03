


typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
int failures;

static _Decimal32
vararg32 (unsigned arg, ...)
{
  int i;
  va_list ap;
  _Decimal32 result;

  __builtin_va_start(ap,arg);
  for (i = 0; i <= arg; i++)
    result = __builtin_va_arg(ap,_Decimal32);
  __builtin_va_end(ap);
  return result;
}

static _Decimal64
vararg64 (unsigned arg, ...)
{
  int i;
  va_list ap;
  _Decimal64 result;

  __builtin_va_start(ap,arg);
  for (i = 0; i <= arg; i++)
    result = __builtin_va_arg(ap,_Decimal64);
  __builtin_va_end(ap);
  return result;
}

static _Decimal128
vararg128 (unsigned arg, ...)
{
  int i;
  va_list ap;
  _Decimal128 result;

  __builtin_va_start(ap,arg);
  for (i = 0; i <= arg; i++)
    result = __builtin_va_arg(ap,_Decimal128);
  __builtin_va_end(ap);
  return result;
}


int main()
{

  if (vararg32 (0, 0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 0.0df)
    __builtin_abort ();
  if (vararg32 (1, 0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 1.0df)
    __builtin_abort ();
  if (vararg32 (2, 0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 2.0df)
    __builtin_abort ();
  if (vararg32 (3, 0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 3.0df)
    __builtin_abort ();
  if (vararg32 (4, 0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 4.0df)
    __builtin_abort ();
  if (vararg32 (5, 0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 5.0df)
    __builtin_abort ();


  if (vararg64 (0, 0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 0.0dd)
    __builtin_abort ();
  if (vararg64 (1, 0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 1.0dd)
    __builtin_abort ();
  if (vararg64 (2, 0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 2.0dd)
    __builtin_abort ();
  if (vararg64 (3, 0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 3.0dd)
    __builtin_abort ();
  if (vararg64 (4, 0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 4.0dd)
    __builtin_abort ();
  if (vararg64 (5, 0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 5.0dd)
    __builtin_abort ();


  if (vararg128 (0, 0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 0.0dl)
    __builtin_abort ();
  if (vararg128 (1, 0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 1.0dl)
    __builtin_abort ();
  if (vararg128 (2, 0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 2.0dl)
    __builtin_abort ();
  if (vararg128 (3, 0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 3.0dl)
    __builtin_abort ();
  if (vararg128 (4, 0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 4.0dl)
    __builtin_abort ();
  if (vararg128 (5, 0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 5.0dl)
    __builtin_abort ();

  return 0;
}
