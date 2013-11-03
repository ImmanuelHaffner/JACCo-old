






int failures;

volatile _Decimal32 sd;
volatile _Decimal64 dd;
volatile _Decimal128 td;
volatile float sf;
volatile double df;
volatile long double tf;

void convert_101 (void) { ; td = 0.000488281251dl; sf = td; if (sf < (0.00048828125f - 0.f) || sf > (0.00048828125f + 0.f)) __builtin_abort ();; }


void
 convert_102
 (void) { ; td = 2.98023223876953125e-8dl; sf = td; if (sf < (2.9802322387695312e-08f - 01.e-13f) || sf > (2.9802322387695312e-08f + 01.e-13f)) __builtin_abort ();; }



void convert_103 (void) { ; df = 1.0e-20; sd = df; if (sd < (1.0e-20df - 0.df) || sd > (1.0e-20df + 0.df)) __builtin_abort ();; }


void convert_104 (void) { ; df = 0.00048828125; sd = df; if (sd < (0.00048828125df - 0.df) || sd > (0.00048828125df + 0.df)) __builtin_abort ();; }
void convert_105 (void) { ; df = 1.0e-96; sd = df; if (sd < (0.dd - 1E-95DF) || sd > (0.dd + 1E-95DF)) __builtin_abort ();; }


void convert_201 (void) { ; sf = 3.402819e+38f; sd = sf; if (sd < (3.402819e+38df - 0.df) || sd > (3.402819e+38df + 0.df)) __builtin_abort ();; }
void convert_202 (void) { ; sd = 3.402819e+38df; sf = sd; if (sf < (3.402819e+38f - 0.f) || sf > (3.402819e+38f + 0.f)) __builtin_abort ();; }
void convert_203 (void) { ; sf = 3.402819e+38f; dd = sf; if (dd < (3.402819e+38dd - 1.e+30dd) || dd > (3.402819e+38dd + 1.e+30dd)) __builtin_abort ();; }
void convert_204 (void) { ; dd = 3.402819e+38dd; sf = dd; if (sf < (3.402819e+38f - 0.f) || sf > (3.402819e+38f + 0.f)) __builtin_abort ();; }
void convert_205 (void) { ; sf = 3.402819e+38f; td = sf; if (td < (3.402819e+38dl - 1.e+30dl) || td > (3.402819e+38dl + 1.e+30dl)) __builtin_abort ();; }
void convert_206 (void) { ; td = 3.402819e+38dl; sf = td; if (sf < (3.402819e+38f - 0.f) || sf > (3.402819e+38f + 0.f)) __builtin_abort ();; }


void convert_211 (void) { ; sd = 9.999998e96df; df = sd; if (df < (9.999998e96 - 0.) || df > (9.999998e96 + 0.)) __builtin_abort ();; }
void convert_212 (void) { ; df = 9.999998e96; sd = df; if (sd < (9.999998e96df - 0.df) || sd > (9.999998e96df + 0.df)) __builtin_abort ();; }


void convert_221 (void) { ; df = 1.79768e+308; dd = df; if (dd < (1.79768e+308dd - 0.dd) || dd > (1.79768e+308dd + 0.dd)) __builtin_abort ();; }
void convert_222 (void) { ; dd = 1.79768e+308dd; df = dd; if (df < (1.79768e+308 - 0.) || df > (1.79768e+308 + 0.)) __builtin_abort ();; }
void convert_223 (void) { ; df = 1.79768e+308; td = df; if (td < (1.79768e+308dl - 1.e292dl) || td > (1.79768e+308dl + 1.e292dl)) __builtin_abort ();; }
void convert_224 (void) { ; td = 1.79768e+308dl; df = td; if (df < (1.79768e+308 - 0.) || df > (1.79768e+308 + 0.)) __builtin_abort ();; }



void convert_301 (void) { ; sd = 100000.DF; sf = sd; if (sf < (100000.F - 0.F) || sf > (100000.F + 0.F)) __builtin_abort ();; }
void convert_302 (void) { ; sf = 100000.F; sd = sf; if (sd < (100000.DF - 0.DF) || sd > (100000.DF + 0.DF)) __builtin_abort ();; }
void convert_303 (void) { ; sd = 999999.DF; sf = sd; if (sf < (999999.F - 0.F) || sf > (999999.F + 0.F)) __builtin_abort ();; }
void convert_304 (void) { ; sf = 999999.F; sd = sf; if (sd < (999999.DF - 0.DF) || sd > (999999.DF + 0.DF)) __builtin_abort ();; }



void convert_311 (void) { ; sd = 1000000.DF; df = sd; if (df < (1000000. - 0.) || df > (1000000. + 0.)) __builtin_abort ();; }
void convert_312 (void) { ; df = 1000000.; sd = df; if (sd < (1000000.DF - 0.DF) || sd > (1000000.DF + 0.DF)) __builtin_abort ();; }
void convert_313 (void) { ; sd = 9999999.DF; df = sd; if (df < (9999999. - 0.) || df > (9999999. + 0.)) __builtin_abort ();; }
void convert_314 (void) { ; df = 9999999.; sd = df; if (sd < (9999999.DF - 0.DF) || sd > (9999999.DF + 0.DF)) __builtin_abort ();; }



void convert_321 (void) { ; dd = 100000000000000.DD; df = dd; if (df < (100000000000000. - 0.) || df > (100000000000000. + 0.)) __builtin_abort ();; }
void convert_322 (void) { ; df = 100000000000000.; dd = df; if (dd < (100000000000000.DD - 0.DD) || dd > (100000000000000.DD + 0.DD)) __builtin_abort ();; };
void convert_323 (void) { ; dd = 999999999999999.DD; df = dd; if (df < (999999999999999. - 0.) || df > (999999999999999. + 0.)) __builtin_abort ();; };
void convert_324 (void) { ; df = 999999999999999.; dd = df; if (dd < (999999999999999.DD - 0.DD) || dd > (999999999999999.DD + 0.DD)) __builtin_abort ();; };



void convert_331 (void) { ; dd = 1000000000000000.DD; tf = dd; if (tf < (1000000000000000.L - 0.L) || tf > (1000000000000000.L + 0.L)) __builtin_abort ();; }
void convert_332 (void) { ; td = 1000000000000000.L; dd = td; if (dd < (1000000000000000.DD - 0.DD) || dd > (1000000000000000.DD + 0.DD)) __builtin_abort ();; }
void convert_333 (void) { ; dd = 9999999999999999.DD; tf = dd; if (tf < (9999999999999999.L - 0.L) || tf > (9999999999999999.L + 0.L)) __builtin_abort ();; }
void convert_334 (void) { ; td = 9999999999999999.L; dd = td; if (dd < (9999999999999999.DD - 0.DD) || dd > (9999999999999999.DD + 0.DD)) __builtin_abort ();; }



void convert_341 (void) { ; td = 100000000000000000.DL; tf = td; if (tf < (100000000000000000.L - 0.L) || tf > (100000000000000000.L + 0.L)) __builtin_abort ();; }
void convert_342 (void) { ; tf = 100000000000000000.L; td = tf; if (td < (100000000000000000.DL - 0.DL) || td > (100000000000000000.DL + 0.DL)) __builtin_abort ();; }
void convert_343 (void) { ; td = 999999999999999999.DL; tf = td; if (tf < (999999999999999999.L - 0.L) || tf > (999999999999999999.L + 0.L)) __builtin_abort ();; }
void convert_344 (void) { ; tf = 999999999999999999.L; td = tf; if (td < (999999999999999999.DL - 0.DL) || td > (999999999999999999.DL + 0.DL)) __builtin_abort ();; }



void
 convert_351
 (void) { ; td = 1000000000000000000000000000000.DL; tf = td; if (tf < (1000000000000000000000000000000.L - 0.L) || tf > (1000000000000000000000000000000.L + 0.L)) __builtin_abort ();; }

void
 convert_352
 (void) { ; tf = 1000000000000000000000000000000.L; td = tf; if (td < (1000000000000000000000000000000.DL - 0.DL) || td > (1000000000000000000000000000000.DL + 0.DL)) __builtin_abort ();; }

void
 convert_353
 (void) { ; td = 9999999999999999999999999999999.DL; tf = td; if (tf < (9999999999999999999999999999999.L - 0.L) || tf > (9999999999999999999999999999999.L + 0.L)) __builtin_abort ();; }

void
 convert_354
 (void) { ; tf = 9999999999999999999999999999999.L; td = tf; if (td < (9999999999999999999999999999999.DL - 0.DL) || td > (9999999999999999999999999999999.DL + 0.DL)) __builtin_abort ();; }




void
 convert_361
 (void) { ; td = 100000000000000000000000000000000.DL; tf = td; if (tf < (100000000000000000000000000000000.L - 0.L) || tf > (100000000000000000000000000000000.L + 0.L)) __builtin_abort ();; }

void
 convert_362
 (void) { ; tf = 100000000000000000000000000000000.L; td = tf; if (td < (100000000000000000000000000000000.DL - 0.DL) || td > (100000000000000000000000000000000.DL + 0.DL)) __builtin_abort ();; }

void
 convert_363
 (void) { ; td = 999999999999999999999999999999999.DL; tf = td; if (tf < (999999999999999999999999999999999.L - 0.L) || tf > (999999999999999999999999999999999.L + 0.L)) __builtin_abort ();; }

void
 convert_364
 (void) { ; tf = 999999999999999999999999999999999.L; td = tf; if (td < (999999999999999999999999999999999.DL - 0.DL) || td > (999999999999999999999999999999999.DL + 0.DL)) __builtin_abort ();; }


int
main ()
{
  convert_101 ();
  convert_102 ();
  convert_103 ();
  convert_104 ();
  convert_105 ();

  convert_201 ();
  convert_202 ();
  convert_203 ();
  convert_204 ();
  convert_205 ();
  convert_206 ();

  convert_211 ();
  convert_212 ();

  convert_221 ();
  convert_222 ();
  convert_223 ();
  convert_224 ();

  convert_301 ();
  convert_302 ();
  convert_303 ();
  convert_304 ();

  convert_311 ();
  convert_312 ();
  convert_313 ();
  convert_314 ();

  convert_321 ();
  convert_322 ();
  convert_323 ();
  convert_324 ();

  if (18 >= 16)
    {
      convert_331 ();
      convert_332 ();
      convert_333 ();
      convert_334 ();
    }

  if (18 >= 18)
    {
      convert_341 ();
      convert_342 ();
      convert_343 ();
      convert_344 ();
    }

  if (18 >= 31)
    {
      convert_351 ();
      convert_352 ();
      convert_353 ();
      convert_354 ();
    }

  if (18 >= 33)
    {
      convert_361 ();
      convert_362 ();
      convert_363 ();
      convert_364 ();
    }

  return 0;
}
