int failures;

volatile _Decimal32 d32;
volatile _Decimal64 d64;
volatile _Decimal128 d128;
volatile int si;
volatile unsigned int ui;
volatile long long sll;
volatile unsigned long long ull;

void
doit ()
{


  d32 = 2147483.E3DF;
  si = d32;
  if (si != 2147483000)
    __builtin_abort ();

  d32 = -2147483.E3DF;
  si = d32;
  if (si != -2147483000)
    __builtin_abort ();



  d32 = 4.294967E9DF;
  ui = d32;
  if (ui != 4294967000U)
    __builtin_abort ();



  d32 = 922.3372E16DF;
  sll = d32;
  if (sll != 9223372000000000000LL)
    __builtin_abort ();

  d32 = -92233.72E14DF;
  sll = d32;
  if (sll != -9223372000000000000LL)
    __builtin_abort ();



  d32 = .1844674E20DF;
  ull = d32;
  if (ull != 18446740000000000000ULL)
    __builtin_abort ();



  d64 = 2.147483647E9DD;
  si = d64;
  if (si != 2147483647)
    __builtin_abort ();

  d64 = -2147483648.DD;
  si = d64;
  if (si != -2147483648)
    __builtin_abort ();



  d64 = 42949.67295E5DD;
  ui = d64;
  if (ui != 4294967295)
    __builtin_abort ();



  d64 = 9.223372036854775E18DD;
  sll = d64;
  if (sll != 9223372036854775000LL)
    __builtin_abort ();

  d64 = -92233720.36854775E11DD;
  sll = d64;
  if (sll != -9223372036854775000LL)
    __builtin_abort ();


  d64 = 1844674407370955.E4DD;
  ull = d64;
  if (ull != 18446744073709550000ULL)
    __builtin_abort ();



  d128 = 2.147483647E9DL;
  si = d128;
  if (si != 2147483647)
    __builtin_abort ();

  d128 = -2147483648.DL;
  si = d128;
  if (si != -2147483648)
    __builtin_abort ();



  d128 = 4294.967295E6DL;
  ui = d128;
  if (ui != 4294967295)
    __builtin_abort ();



  d128 = 9223372036854775807.DL;
  sll = d128;
  if (sll != 9223372036854775807LL)
    __builtin_abort ();

  d128 = -9.223372036854775808E19DL;
  sll = d128;
  if (sll != -9223372036854775807LL - 1LL)
    __builtin_abort ();


  d128 = 18446744073709551615.DL;
  ull = d128;
  if (ull != 18446744073709551615ULL)
    __builtin_abort ();
}

int
main ()
{


  if (sizeof (int) != 4 || sizeof (long long) != 8)
    return 0;

  doit ();

  return 0;
}
