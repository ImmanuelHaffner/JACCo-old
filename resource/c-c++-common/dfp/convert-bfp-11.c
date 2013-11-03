






int failures;

volatile _Decimal32 sd;
volatile _Decimal64 dd;
volatile _Decimal128 td;
volatile float sf;
volatile double df;
volatile long double tf;


void convert_101 (void) { ; sd = 9.999998e96df; tf = sd; if (tf < (9.999998e96L - 1.e+81L) || tf > (9.999998e96L + 1.e+81L)) __builtin_abort ();; }
void convert_102 (void) { ; tf = 9.999998e96L; sd = tf; if (sd < (9.999998e96df - 0.df) || sd > (9.999998e96df + 0.df)) __builtin_abort ();; }


void convert_201 (void) { ; tf = 1.79768e+308l; dd = tf; if (dd < (1.79768e+308dd - 0.dd) || dd > (1.79768e+308dd + 0.dd)) __builtin_abort ();; }
void convert_202 (void) { ; dd = 1.79768e+308dd; tf = dd; if (tf < (1.79768e+308l - 2.e292l) || tf > (1.79768e+308l + 2.e292l)) __builtin_abort ();; }
void convert_203 (void) { ; tf = 1.79768e+308l; td = tf; if (td < (1.79768e+308dl - 1.e292dl) || td > (1.79768e+308dl + 1.e292dl)) __builtin_abort ();; }
void convert_204 (void) { ; td = 1.79768e+308dl; tf = td; if (tf < (1.79768e+308l - 2.e292l) || tf > (1.79768e+308l + 2.e292l)) __builtin_abort ();; }


void convert_301 (void) { ; dd = 1.8e+308dd; tf = dd; if (__builtin_isinfl (tf) == 0) __builtin_abort ();; if (__builtin_signbitl (tf) != 0) __builtin_abort ();; }
void convert_302 (void) { ; dd = 9.9e+384dd; tf = dd; if (__builtin_isinfl (tf) == 0) __builtin_abort ();; if (__builtin_signbitl (tf) != 0) __builtin_abort ();; }
void convert_303 (void) { ; td = 1.8e+308dl; tf = td; if (__builtin_isinfl (tf) == 0) __builtin_abort ();; if (__builtin_signbitl (tf) != 0) __builtin_abort ();; }
void convert_304 (void) { ; td = 9.9e+384dl; tf = td; if (__builtin_isinfl (tf) == 0) __builtin_abort ();; if (__builtin_signbitl (tf) != 0) __builtin_abort ();; }

void convert_311 (void) { ; tf = 1.0e+97L; sd = tf; if (__builtin_isinfd32 (sd) == 0) __builtin_abort ();; if (__builtin_signbitd32 (sd) != 0) __builtin_abort ();; }
void convert_312 (void) { ; tf = 1.6e+308L; sd = tf; if (__builtin_isinfd32 (sd) == 0) __builtin_abort ();; if (__builtin_signbitd32 (sd) != 0) __builtin_abort ();; }

int
main ()
{
  if (sizeof (long double) != 16)
    return 0;

  convert_101 ();
  convert_102 ();

  convert_201 ();
  convert_202 ();
  convert_203 ();
  convert_204 ();

  convert_301 ();
  convert_302 ();
  convert_303 ();
  convert_304 ();
  convert_311 ();
  convert_312 ();

  return 0;
}
