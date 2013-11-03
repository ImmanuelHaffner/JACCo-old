int failures;

















volatile _Decimal32 d32;
volatile _Decimal64 d64;
volatile _Decimal128 d128;

volatile signed int si;
volatile unsigned int usi;
volatile unsigned long long udi;

int
main ()
{


  usi = 9.999999E96DF;
  if (usi != (2147483647 * 2U + 1U))
    __builtin_abort ();

  usi = 9.999999999999999E384DD;
  if (usi != (2147483647 * 2U + 1U))
    __builtin_abort ();

  usi = 9.999999999999999999999999999999999E6144DL;
  if (usi != (2147483647 * 2U + 1U))
    __builtin_abort ();


  si = 9.999999E96DF;
  if (si != 2147483647)
    __builtin_abort ();

  si = 9.999999999999999E384DD;
  if (si != 2147483647)
    __builtin_abort ();

  si = 9.999999999999999999999999999999999E6144DL;
  if (si != 2147483647)
    __builtin_abort ();

  si = - 9.999999E96DF;
  if (si != (-2147483647 - 1))
    __builtin_abort ();

  si = - 9.999999999999999E384DD;
  if (si != (-2147483647 - 1))
    __builtin_abort ();

  si = - 9.999999999999999999999999999999999E6144DL;
  if (si != (-2147483647 - 1))
    __builtin_abort ();

  return 0;
}
