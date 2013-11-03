




int failures;







_Decimal32 d32;
_Decimal64 d64;
_Decimal128 d128;
unsigned int ui;
unsigned long ul;
unsigned long long ull;
int si;
long sl;
long long sll;
_Bool b;

void
init_dfp_1 (void)
{
  d32 = 456.789df;
  d64 = 23.456789dd;
  d128 = 1234.5678dl;
}
void
init_dfp_2 (void)
{
  d32 = 1.23df;
  d64 = -3.4dd;
  d128 = 0.00003dl;
}

void
init_dfp_3 (void)
{
  d32 = 0.0DF;
  d64 = 0.0DD;
  d128 = 0.0DL;
}

void
init_unsigned_int (void)
{
  ui = 987U;
  ul = 345678UL;
  ull = 1234567ULL;
}

void
init_signed_int (void)
{
  si = -987;
  sl = -345678;
  sll = -1234567;
}

int
main ()
{





  init_dfp_1 ();

  ui = d32;
  if (ui != 456U)
    __builtin_abort ();
  ul = d32;
  if (ul != 456UL)
    __builtin_abort ();
  ull = d32;
  if (ull != 456ULL)
    __builtin_abort ();

  ui = d64;
  if (ui != 23U)
    __builtin_abort ();
  ul = d64;
  if (ul != 23UL)
    __builtin_abort ();
  ull = d64;
  if (ull != 23ULL)
    __builtin_abort ();

  ui = d128;
  if (ui != 1234U)
    __builtin_abort ();
  ul = d128;
  if (ul != 1234UL)
    __builtin_abort ();
  ull = d128;
  if (ull != 1234ULL)
    __builtin_abort ();




  init_dfp_2 ();

  b = d32;
  if (!b)
    __builtin_abort ();
  b = d64;
  if (!b)
    __builtin_abort ();
  b = d128;
  if (!b)
    __builtin_abort ();


  init_unsigned_int ();

  d32 = ui;
  if (d32 != 987.0df)
    __builtin_abort ();
  d32 = ul;
  if (d32 != 345678.0df)
    __builtin_abort ();
  d32 = ull;
  if (d32 != 1234567.df)
    __builtin_abort ();

  d64 = ui;
  if (d64 != 987.0dd)
    __builtin_abort ();
  d64 = ul;
  if (d64 != 345678.0dd)
    __builtin_abort ();
  d64 = ull;
  if (d64 != 1234567.dd)
    __builtin_abort ();

  d128 = ui;
  if (d128 != 987.0dl)
    __builtin_abort ();
  d128 = ul;
  if (d128 != 345678.0dl)
    __builtin_abort ();
  d128 = ull;
  if (d128 != 1234567.dl)
    __builtin_abort ();


  init_signed_int ();

  d32 = si;
  if (d32 != -987.0df)
    __builtin_abort ();
  d32 = sl;
  if (d32 != -345678.0df)
    __builtin_abort ();
  d32 = sll;
  if (d32 != -1234567.df)
    __builtin_abort ();

  d64 = si;
  if (d64 != -987.0dd)
    __builtin_abort ();
  d64 = sl;
  if (d64 != -345678.0dd)
    __builtin_abort ();
  d64 = sll;
  if (d64 != -1234567.dd)
    __builtin_abort ();

  d128 = si;
  if (d128 != -987.0dl)
    __builtin_abort ();
  d128 = sl;
  if (d128 != -345678.0dl)
    __builtin_abort ();
  d128 = sll;
  if (d128 != -1234567.dl)
    __builtin_abort ();


  init_dfp_3 ();

  b = d32;
  if (b)
    __builtin_abort ();
  b = d64;
  if (b)
    __builtin_abort ();
  b = d128;
  if (b)
    __builtin_abort ();

  return 0;
}
