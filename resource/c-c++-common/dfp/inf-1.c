



int failures;

int main()
{

  if (9999999.E90DF + 1.E90df != __builtin_infd32 ())
    __builtin_abort ();

  if (!__builtin_isinfd32 (9999999.E90DF + 1.E90df))
    __builtin_abort ();

  if (9.999999999999999E384dd + .000000000000001e384dd
      != __builtin_infd32 ())
    __builtin_abort ();

  if (-9999999.E90DF - 1.E90df != -__builtin_infd32 ())
    __builtin_abort ();

  if (!__builtin_isinfd32 (9.999999999999999E384dd + .000000000000001e384dd))
    __builtin_abort ();

  if (7.999999999999999999999999999999999E6144dl + 3.0E6144dl
      != __builtin_infd32 ())
    __builtin_abort ();

  if (__builtin_infd32 () * __builtin_infd32 () != __builtin_infd32 ())
    __builtin_abort ();

  if (__builtin_infd32 () * 2 != __builtin_infd32 ())
    __builtin_abort ();

  if (__builtin_infd64 () * -5 != -__builtin_infd32 ())
    __builtin_abort ();

  if (!__builtin_isinfd128 (__builtin_infd32 () / 4))
    __builtin_abort ();

  if (__builtin_infd64 () != __builtin_infd128 ())
    __builtin_abort ();

  if (!__builtin_isinfd64 (__builtin_infd128 ()))
    __builtin_abort ();

  if (__builtin_finited64 (__builtin_infd32 () * 4))
    __builtin_abort ();

  if (!__builtin_finited128 (9.999999E90DL - 1.E90dd))
    __builtin_abort ();

  if (__builtin_finited128 (__builtin_infd32 () *__builtin_infd128 ()))
    __builtin_abort ();

  if (__builtin_finited32 (__builtin_nand32 ("")))
    __builtin_abort ();

  return 0;
}
