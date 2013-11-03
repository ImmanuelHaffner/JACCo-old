





int failures;

volatile _Decimal32 sd;
volatile _Decimal64 dd;
volatile _Decimal128 td;
volatile float sf;
volatile double df;


void convert_301 (void) { ; sd = 4.e+38df; sf = sd; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) != 0) __builtin_abort ();; }
void convert_303 (void) { ; dd = 4.e+38dd; sf = dd; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) != 0) __builtin_abort ();; }
void convert_302 (void) { ; sd = 9.9e+384df; sf = sd; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) != 0) __builtin_abort ();; }
void convert_304 (void) { ; dd = 9.9e+384dd; sf = dd; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) != 0) __builtin_abort ();; }
void convert_305 (void) { ; td = 4.e+38dl; sf = td; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) != 0) __builtin_abort ();; }
void convert_306 (void) { ; td = 1.e+39dl; sf = td; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) != 0) __builtin_abort ();; }
void convert_311 (void) { ; sd = -4.e+38df; sf = sd; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) == 0) __builtin_abort ();; }
void convert_312 (void) { ; dd = -4.e+38dd; sf = dd; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) == 0) __builtin_abort ();; }
void convert_313 (void) { ; sd = -9.9e+384df; sf = sd; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) == 0) __builtin_abort ();; }
void convert_314 (void) { ; dd = -9.9e+384dd; sf = dd; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) == 0) __builtin_abort ();; }
void convert_315 (void) { ; td = -4.e+38dl; sf = td; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) == 0) __builtin_abort ();; }
void convert_316 (void) { ; td = -1.e+39dl; sf = td; if (__builtin_isinff (sf) == 0) __builtin_abort ();; if (__builtin_signbitf (sf) == 0) __builtin_abort ();; }

void convert_321 (void) { ; dd = 1.8e+308dd; df = dd; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) != 0) __builtin_abort ();; }
void convert_322 (void) { ; dd = 9.9e+384dd; df = dd; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) != 0) __builtin_abort ();; }
void convert_323 (void) { ; td = 1.8e+308dl; df = td; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) != 0) __builtin_abort ();; }
void convert_324 (void) { ; td = 9.9e+384dl; df = td; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) != 0) __builtin_abort ();; }
void convert_325 (void) { ; dd = 1.e309dd; df = dd; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) != 0) __builtin_abort ();; }
void convert_326 (void) { ; td = 1.e309dl; df = td; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) != 0) __builtin_abort ();; }
void convert_331 (void) { ; dd = -1.8e+308dd; df = dd; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) == 0) __builtin_abort ();; }
void convert_332 (void) { ; dd = -9.9e+384dd; df = dd; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) == 0) __builtin_abort ();; }
void convert_333 (void) { ; td = -1.8e+308dl; df = td; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) == 0) __builtin_abort ();; }
void convert_334 (void) { ; td = -9.9e+384dl; df = td; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) == 0) __builtin_abort ();; }
void convert_335 (void) { ; dd = -1.e309dd; df = dd; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) == 0) __builtin_abort ();; }
void convert_336 (void) { ; td = -1.e309dl; df = td; if (__builtin_isinf (df) == 0) __builtin_abort ();; if (__builtin_signbit (df) == 0) __builtin_abort ();; }

void convert_341 (void) { ; df = 1.0e+97; sd = df; if (__builtin_isinfd32 (sd) == 0) __builtin_abort ();; if (__builtin_signbitd32 (sd) != 0) __builtin_abort ();; }
void convert_342 (void) { ; df = 1.6e+308; sd = df; if (__builtin_isinfd32 (sd) == 0) __builtin_abort ();; if (__builtin_signbitd32 (sd) != 0) __builtin_abort ();; }
void convert_351 (void) { ; df = -1.0e+97; sd = df; if (__builtin_isinfd32 (sd) == 0) __builtin_abort ();; if (__builtin_signbitd32 (sd) == 0) __builtin_abort ();; }
void convert_352 (void) { ; df = -1.6e+308; sd = df; if (__builtin_isinfd32 (sd) == 0) __builtin_abort ();; if (__builtin_signbitd32 (sd) == 0) __builtin_abort ();; }

int
main ()
{
  convert_301 ();
  convert_302 ();
  convert_303 ();
  convert_304 ();
  convert_305 ();
  convert_306 ();
  convert_311 ();
  convert_312 ();
  convert_313 ();
  convert_314 ();
  convert_315 ();
  convert_316 ();

  convert_321 ();
  convert_322 ();
  convert_323 ();
  convert_324 ();
  convert_325 ();
  convert_326 ();
  convert_331 ();
  convert_332 ();
  convert_333 ();
  convert_334 ();
  convert_335 ();
  convert_336 ();

  convert_341 ();
  convert_342 ();
  convert_351 ();
  convert_352 ();

  return 0;
}
