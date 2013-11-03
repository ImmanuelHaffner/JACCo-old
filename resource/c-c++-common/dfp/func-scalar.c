



int failures;




_Decimal32
arg0_32 (_Decimal32 arg0, _Decimal32 arg1, _Decimal32 arg2,
  _Decimal32 arg3, _Decimal32 arg4, _Decimal32 arg5)
{
  return arg0;
}

_Decimal32
arg1_32 (_Decimal32 arg0, _Decimal32 arg1, _Decimal32 arg2,
  _Decimal32 arg3, _Decimal32 arg4, _Decimal32 arg5)
{
  return arg1;
}

_Decimal32
arg2_32 (_Decimal32 arg0, _Decimal32 arg1, _Decimal32 arg2,
  _Decimal32 arg3, _Decimal32 arg4, _Decimal32 arg5)
{
  return arg2;
}

_Decimal32
arg3_32 (_Decimal32 arg0, _Decimal32 arg1, _Decimal32 arg2,
  _Decimal32 arg3, _Decimal32 arg4, _Decimal32 arg5)
{
  return arg3;
}

_Decimal32
arg4_32 (_Decimal32 arg0, _Decimal32 arg1, _Decimal32 arg2,
  _Decimal32 arg3, _Decimal32 arg4, _Decimal32 arg5)
{
  return arg4;
}

_Decimal32
arg5_32 (_Decimal32 arg0, _Decimal32 arg1, _Decimal32 arg2,
  _Decimal32 arg3, _Decimal32 arg4, _Decimal32 arg5)
{
  return arg5;
}





_Decimal64
arg0_64 (_Decimal64 arg0, _Decimal64 arg1, _Decimal64 arg2,
  _Decimal64 arg3, _Decimal64 arg4, _Decimal64 arg5)
{
  return arg0;
}

_Decimal64
arg1_64 (_Decimal64 arg0, _Decimal64 arg1, _Decimal64 arg2,
  _Decimal64 arg3, _Decimal64 arg4, _Decimal64 arg5)
{
  return arg1;
}

_Decimal64
arg2_64 (_Decimal64 arg0, _Decimal64 arg1, _Decimal64 arg2,
  _Decimal64 arg3, _Decimal64 arg4, _Decimal64 arg5)
{
  return arg2;
}

_Decimal64
arg3_64 (_Decimal64 arg0, _Decimal64 arg1, _Decimal64 arg2,
  _Decimal64 arg3, _Decimal64 arg4, _Decimal64 arg5)
{
  return arg3;
}

_Decimal64
arg4_64 (_Decimal64 arg0, _Decimal64 arg1, _Decimal64 arg2,
  _Decimal64 arg3, _Decimal64 arg4, _Decimal64 arg5)
{
  return arg4;
}

_Decimal64
arg5_64 (_Decimal64 arg0, _Decimal64 arg1, _Decimal64 arg2,
  _Decimal64 arg3, _Decimal64 arg4, _Decimal64 arg5)
{
  return arg5;
}





_Decimal128
arg0_128 (_Decimal128 arg0, _Decimal128 arg1, _Decimal128 arg2,
  _Decimal128 arg3, _Decimal128 arg4, _Decimal128 arg5)
{
  return arg0;
}

_Decimal128
arg1_128 (_Decimal128 arg0, _Decimal128 arg1, _Decimal128 arg2,
  _Decimal128 arg3, _Decimal128 arg4, _Decimal128 arg5)
{
  return arg1;
}

_Decimal128
arg2_128 (_Decimal128 arg0, _Decimal128 arg1, _Decimal128 arg2,
  _Decimal128 arg3, _Decimal128 arg4, _Decimal128 arg5)
{
  return arg2;
}

_Decimal128
arg3_128 (_Decimal128 arg0, _Decimal128 arg1, _Decimal128 arg2,
  _Decimal128 arg3, _Decimal128 arg4, _Decimal128 arg5)
{
  return arg3;
}

_Decimal128
arg4_128 (_Decimal128 arg0, _Decimal128 arg1, _Decimal128 arg2,
  _Decimal128 arg3, _Decimal128 arg4, _Decimal128 arg5)
{
  return arg4;
}

_Decimal128
arg5_128 (_Decimal128 arg0, _Decimal128 arg1, _Decimal128 arg2,
  _Decimal128 arg3, _Decimal128 arg4, _Decimal128 arg5)
{
  return arg5;
}



int
main ()
{

  if (arg0_32 (0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 0.0df)
    __builtin_abort ();
  if (arg1_32 (0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 1.0df)
    __builtin_abort ();
  if (arg2_32 (0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 2.0df)
    __builtin_abort ();
  if (arg3_32 (0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 3.0df)
    __builtin_abort ();
  if (arg4_32 (0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 4.0df)
    __builtin_abort ();
  if (arg5_32 (0.0df, 1.0df, 2.0df, 3.0df, 4.0df, 5.0df) != 5.0df)
    __builtin_abort ();


  if (arg0_64 (0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 0.0dd)
    __builtin_abort ();
  if (arg1_64 (0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 1.0dd)
    __builtin_abort ();
  if (arg2_64 (0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 2.0dd)
    __builtin_abort ();
  if (arg3_64 (0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 3.0dd)
    __builtin_abort ();
  if (arg4_64 (0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 4.0dd)
    __builtin_abort ();
  if (arg5_64 (0.0dd, 1.0dd, 2.0dd, 3.0dd, 4.0dd, 5.0dd) != 5.0dd)
    __builtin_abort ();


  if (arg0_128 (0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 0.0dl)
    __builtin_abort ();
  if (arg1_128 (0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 1.0dl)
    __builtin_abort ();
  if (arg2_128 (0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 2.0dl)
    __builtin_abort ();
  if (arg3_128 (0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 3.0dl)
    __builtin_abort ();
  if (arg4_128 (0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 4.0dl)
    __builtin_abort ();
  if (arg5_128 (0.0dl, 1.0dl, 2.0dl, 3.0dl, 4.0dl, 5.0dl) != 5.0dl)
    __builtin_abort ();

  return 0;
}
