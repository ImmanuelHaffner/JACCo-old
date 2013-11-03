





int failures;

volatile _Decimal32 sd;
volatile _Decimal64 dd;
volatile _Decimal128 td;
volatile float sf;
volatile double df;


void convert_401 (void) { ; sd = 1.e-39df; sf = sd; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }
void convert_402 (void) { ; sd = -1.e-39df; sf = sd; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }
void convert_403 (void) { ; sd = 1.1e-38df; sf = sd; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }
void convert_404 (void) { ; sd = -1.1e-38df; sf = sd; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }

void convert_411 (void) { ; dd = 1.e-39dd; sf = dd; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }
void convert_412 (void) { ; dd = -1.e-39dd; sf = dd; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }
void convert_413 (void) { ; dd = 1.1e-38dd; sf = dd; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }
void convert_414 (void) { ; dd = -1.1e-38dd; sf = dd; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }

void convert_421 (void) { ; dd = 3.e-309dd; df = dd; if (df < (0. - ((double)2.22507385850720138309e-308L)) || df > (0. + ((double)2.22507385850720138309e-308L))) __builtin_abort ();; }
void convert_422 (void) { ; dd = -3.e-309dd; df = dd; if (df < (0. - ((double)2.22507385850720138309e-308L)) || df > (0. + ((double)2.22507385850720138309e-308L))) __builtin_abort ();; }
void convert_423 (void) { ; dd = 2.e-308dd; df = dd; if (df < (0. - ((double)2.22507385850720138309e-308L)) || df > (0. + ((double)2.22507385850720138309e-308L))) __builtin_abort ();; }
void convert_424 (void) { ; dd = -2.e-308dd; df = dd; if (df < (0. - ((double)2.22507385850720138309e-308L)) || df > (0. + ((double)2.22507385850720138309e-308L))) __builtin_abort ();; }

void convert_431 (void) { ; td = 1.e-39dl; sf = td; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }
void convert_432 (void) { ; td = -1.e-39dl; sf = td; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }
void convert_433 (void) { ; td = 1.1e-38dl; sf = td; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }
void convert_434 (void) { ; td = -1.1e-38dl; sf = td; if (sf < (0.f - 1.17549435082228750797e-38F) || sf > (0.f + 1.17549435082228750797e-38F)) __builtin_abort ();; }

void convert_441 (void) { ; td = 3.e-309dl; df = td; if (df < (0. - ((double)2.22507385850720138309e-308L)) || df > (0. + ((double)2.22507385850720138309e-308L))) __builtin_abort ();; }
void convert_442 (void) { ; td = -3.e-309dl; df = td; if (df < (0. - ((double)2.22507385850720138309e-308L)) || df > (0. + ((double)2.22507385850720138309e-308L))) __builtin_abort ();; }
void convert_443 (void) { ; td = 2.e-308dl; df = td; if (df < (0. - ((double)2.22507385850720138309e-308L)) || df > (0. + ((double)2.22507385850720138309e-308L))) __builtin_abort ();; }
void convert_444 (void) { ; td = -2.e-308dl; df = td; if (df < (0. - ((double)2.22507385850720138309e-308L)) || df > (0. + ((double)2.22507385850720138309e-308L))) __builtin_abort ();; }

int
main ()
{
  convert_401 ();
  convert_402 ();
  convert_403 ();
  convert_404 ();

  convert_411 ();
  convert_412 ();
  convert_413 ();
  convert_414 ();

  convert_421 ();
  convert_422 ();
  convert_423 ();
  convert_424 ();

  convert_431 ();
  convert_432 ();
  convert_433 ();
  convert_434 ();

  convert_441 ();
  convert_442 ();
  convert_443 ();
  convert_444 ();

  return 0;
}
