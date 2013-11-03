



int failures;

int main()
{


  if (__builtin_nand32("") == __builtin_nand32(""))
    __builtin_abort ();

  if (__builtin_nand64("") == __builtin_nand64(""))
    __builtin_abort ();

  if (__builtin_nand128("") == __builtin_nand128(""))
    __builtin_abort ();

  if (!(__builtin_nand32("") != __builtin_nand32("")))
    __builtin_abort ();

  if (!(__builtin_nand64("") != __builtin_nand64("")))
    __builtin_abort ();

  if (!(__builtin_nand128("") != __builtin_nand128("")))
    __builtin_abort ();

  if (__builtin_nand32("") > __builtin_nand32(""))
    __builtin_abort ();

  if (__builtin_nand64("") >= __builtin_nand64(""))
    __builtin_abort ();

  if (__builtin_nand128("") < __builtin_nand128(""))
    __builtin_abort ();

  if (-__builtin_nand128("") < +__builtin_nand128(""))
    __builtin_abort ();


  if (0.0df/0.0dl == __builtin_nand32(""))
    __builtin_abort ();


  if (!__builtin_isnand32 (0.0df * __builtin_infd32()))
    __builtin_abort ();

  if (!__builtin_isnand64 (0.0dd * __builtin_infd64()))
    __builtin_abort ();

  if (!__builtin_isnand128 (0.0dd * __builtin_infd128()))
    __builtin_abort ();


  if (!__builtin_isnand32 (__builtin_infd32() - __builtin_infd32()))
    __builtin_abort ();

  if (!__builtin_isnand64 (__builtin_infd64() - __builtin_infd64()))
    __builtin_abort ();

  if (!__builtin_isnand128 (__builtin_infd128() - __builtin_infd128()))
    __builtin_abort ();


  if (!__builtin_isnand32 (__builtin_infd32()/__builtin_infd32()) )
    __builtin_abort ();

  if (!__builtin_isnand64 (__builtin_infd64()/__builtin_infd64()) )
    __builtin_abort ();

  if (!__builtin_isnand128 (__builtin_infd128()/__builtin_infd128()) )
    __builtin_abort ();


  if ((0.0dd/0.0df) == (0.0dd/0.0df))
    __builtin_abort ();

  if (__builtin_nand32("") < __builtin_infd32())
    __builtin_abort ();

  if (__builtin_nand32("") >= __builtin_infd32())
    __builtin_abort ();



  if (!__builtin_isnand32(__builtin_nand32("")))
    __builtin_abort ();

  if (!__builtin_isnand64(__builtin_nand64("")))
    __builtin_abort ();

  if (!__builtin_isnand128(__builtin_nand128("")))
    __builtin_abort ();

  if (!__builtin_isnand128(8.0df * __builtin_nand128("")))
    __builtin_abort ();

  if (!__builtin_isnand32(8.1dl - __builtin_nand32("")))
    __builtin_abort ();

  if (!__builtin_isnand128(__builtin_nand64("") + __builtin_nand128("")))
    __builtin_abort ();

  return 0;
}
