


int failures;

_Decimal32 d32;
_Decimal64 d64;
_Decimal128 d128;

static float f = 2.f;
static double d = 2.l;

int
main (void)
{

  d32 = 1.2df;
  d64 = 1.2dd;
  d128 = 1.2dl;

  if (d32 != (_Decimal32) d64)
    __builtin_abort ();
  if (d32 != (_Decimal32) d128)
    __builtin_abort ();

  if (d64 != (_Decimal64) d32)
    __builtin_abort ();
  if (d64 != (_Decimal64) d128)
    __builtin_abort ();

  if (d128 != (_Decimal128) d32)
    __builtin_abort ();
  if (d128 != (_Decimal128) d64)
    __builtin_abort ();





  d32 = 2.0df;
  d64 = 2.0dd;
  d128 = 2.0dl;


  if ((float) d32 != 2.0f)
    __builtin_abort ();
  if ((double) d32 != 2.0l)
    __builtin_abort ();
  if ((float) d64 != 2.0f)
    __builtin_abort ();
  if ((double) d64 != 2.0l)
    __builtin_abort ();
  if ((float) d128 != 2.0f)
    __builtin_abort ();
  if ((double) d128 != 2.0l)
    __builtin_abort ();


  if (d32 != (_Decimal32) f)
    __builtin_abort ();
  if (d64 != (_Decimal64) f)
    __builtin_abort ();
  if (d128 != (_Decimal128) f)
    __builtin_abort ();


  if (d32 != (_Decimal32) d)
    __builtin_abort ();
  if (d64 != (_Decimal64) d)
    __builtin_abort ();
  if (d128 != (_Decimal128) d)
    __builtin_abort ();

  return 0;
}
