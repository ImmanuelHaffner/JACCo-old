




int failures;

int main()
{
  _Decimal32 d32;
  _Decimal64 d64;
  _Decimal128 d128;



  d32 = 123.45f;
  if (d32/-0.0df != -__builtin_infd32())
    __builtin_abort ();
  if (123.45df/-0.0df != -__builtin_infd32())
    __builtin_abort ();

  d64 = 123.45f;
  if (d64/-0.0dd != -__builtin_infd64())
    __builtin_abort ();
  if (123.45dd/-0.0dd != -__builtin_infd64())
    __builtin_abort ();

  d128 = 123.45f;
  if (d128/-0.0dl != -__builtin_infd64())
    __builtin_abort ();
  if (123.45dl/-0.0dl != -__builtin_infd128())
    __builtin_abort ();

  d32 = 0.0df;
  if (!__builtin_isnand32(-(d32/-0.0df)))
    __builtin_abort ();
  if (!__builtin_isnand32(-(0.0df/-0.0df)))
    __builtin_abort ();

  d64 = 0.0dd;
  if (!__builtin_isnand64(-(d64/-0.0dd)))
    __builtin_abort ();
  if (!__builtin_isnand64(-(0.0dd/-0.0dd)))
    __builtin_abort ();

  d128 = 0.0dl;
  if (!__builtin_isnand128(-(d128/-0.0dl)))
    __builtin_abort ();
  if (!__builtin_isnand128(-(0.0dl/-0.0dl)))
    __builtin_abort ();

  return 0;
}
