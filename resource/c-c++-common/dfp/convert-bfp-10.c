

int failures;

volatile _Decimal32 sd;
volatile _Decimal64 dd;
volatile _Decimal128 td;
volatile float sf;
volatile double df;


void convert_111 (void) { ; sf = 1.2e-38f; sd = sf; if (sd < (1.2e-38df - 0.df) || sd > (1.2e-38df + 0.df)) __builtin_abort ();; }
void convert_112 (void) { ; sf = 1.1e-38f; sd = sf; if (sd < (1.1e-38df - 0.df) || sd > (1.1e-38df + 0.df)) __builtin_abort ();; }
void convert_113 (void) { ; sf = 1.1e-40f; sd = sf; if (sd < (1.1e-40df - 1.1e-45df) || sd > (1.1e-40df + 1.1e-45df)) __builtin_abort ();; }

void convert_121 (void) { ; sd = 1.2e-38df; sf = sd; if (sf < (1.2e-38f - 0.f) || sf > (1.2e-38f + 0.f)) __builtin_abort ();; }
void convert_122 (void) { ; sd = 1.1e-38df; sf = sd; if (sf < (1.1e-38f - 0.f) || sf > (1.1e-38f + 0.f)) __builtin_abort ();; }

void convert_131 (void) { ; sf = -1.2e-38f; sd = sf; if (sd < (-1.2e-38df - 0.df) || sd > (-1.2e-38df + 0.df)) __builtin_abort ();; }
void convert_132 (void) { ; sf = -1.1e-38f; sd = sf; if (sd < (-1.1e-38df - 0.df) || sd > (-1.1e-38df + 0.df)) __builtin_abort ();; }

void convert_141 (void) { ; sd = -1.2e-38df; sf = sd; if (sf < (-1.2e-38f - 0.f) || sf > (-1.2e-38f + 0.f)) __builtin_abort ();; }
void convert_142 (void) { ; sd = -1.1e-38df; sf = sd; if (sf < (-1.1e-38f - 0.f) || sf > (-1.1e-38f + 0.f)) __builtin_abort ();; }


void convert_211 (void) { ; df = 1.2e-38; sd = df; if (sd < (1.2e-38df - 0.df) || sd > (1.2e-38df + 0.df)) __builtin_abort ();; }
void convert_212 (void) { ; df = 1.1e-38; sd = df; if (sd < (1.1e-38df - 0.df) || sd > (1.1e-38df + 0.df)) __builtin_abort ();; }
void convert_213 (void) { ; df = 1.e-40; sd = df; if (sd < (1.e-40df - 0.df) || sd > (1.e-40df + 0.df)) __builtin_abort ();; }
void convert_214 (void) { ; df = 8.e-44; sd = df; if (sd < (8.e-44df - 0.df) || sd > (8.e-44df + 0.df)) __builtin_abort ();; }
void convert_215 (void) { ; df = 9.e-44; sd = df; if (sd < (9.e-44df - 0.df) || sd > (9.e-44df + 0.df)) __builtin_abort ();; }
void convert_216 (void) { ; df = 8.e-46; sd = df; if (sd < (8.e-46df - 0.df) || sd > (8.e-46df + 0.df)) __builtin_abort ();; }
void convert_217 (void) { ; df = 7.e-46; sd = df; if (sd < (7.e-46df - 0.df) || sd > (7.e-46df + 0.df)) __builtin_abort ();; }

void convert_221 (void) { ; sd = 1.2e-38df; df = sd; if (df < (1.2e-38 - 1.e-53) || df > (1.2e-38 + 1.e-53)) __builtin_abort ();; }
void convert_222 (void) { ; sd = 1.1e-38df; df = sd; if (df < (1.1e-38 - 1.e-53) || df > (1.1e-38 + 1.e-53)) __builtin_abort ();; }
void convert_223 (void) { ; sd = 1.e-40df; df = sd; if (df < (1.e-40 - 0.) || df > (1.e-40 + 0.)) __builtin_abort ();; }
void convert_224 (void) { ; sd = 8.e-44df; df = sd; if (df < (8.e-44 - 0.) || df > (8.e-44 + 0.)) __builtin_abort ();; }
void convert_225 (void) { ; sd = 9.e-44df; df = sd; if (df < (9.e-44 - 0.) || df > (9.e-44 + 0.)) __builtin_abort ();; }
void convert_226 (void) { ; sd = 8.e-46df; df = sd; if (df < (8.e-46 - 0.) || df > (8.e-46 + 0.)) __builtin_abort ();; }
void convert_227 (void) { ; sd = 7.e-46df; df = sd; if (df < (7.e-46 - 0.) || df > (7.e-46 + 0.)) __builtin_abort ();; }

void convert_231 (void) { ; df = -1.2e-38; sd = df; if (sd < (-1.2e-38df - 0.df) || sd > (-1.2e-38df + 0.df)) __builtin_abort ();; }
void convert_232 (void) { ; df = -1.1e-38f; sd = df; if (sd < (-1.1e-38df - 0.df) || sd > (-1.1e-38df + 0.df)) __builtin_abort ();; }
void convert_233 (void) { ; df = -1.e-40; sd = df; if (sd < (-1.e-40df - 0.df) || sd > (-1.e-40df + 0.df)) __builtin_abort ();; }
void convert_234 (void) { ; df = -8.e-44; sd = df; if (sd < (-8.e-44df - 0.df) || sd > (-8.e-44df + 0.df)) __builtin_abort ();; }
void convert_235 (void) { ; df = -9.e-44; sd = df; if (sd < (-9.e-44df - 0.df) || sd > (-9.e-44df + 0.df)) __builtin_abort ();; }
void convert_236 (void) { ; df = -8.e-46; sd = df; if (sd < (-8.e-46df - 0.df) || sd > (-8.e-46df + 0.df)) __builtin_abort ();; }
void convert_237 (void) { ; df = -7.e-46; sd = df; if (sd < (-7.e-46df - 0.df) || sd > (-7.e-46df + 0.df)) __builtin_abort ();; }

void convert_241 (void) { ; sd = -1.2e-38df; df = sd; if (df < (-1.2e-38 - 1.e-53) || df > (-1.2e-38 + 1.e-53)) __builtin_abort ();; }
void convert_242 (void) { ; sd = -1.1e-38df; df = sd; if (df < (-1.1e-38 - 1.e-53) || df > (-1.1e-38 + 1.e-53)) __builtin_abort ();; }
void convert_243 (void) { ; sd = -1.e-40df; df = sd; if (df < (-1.e-40 - 0.) || df > (-1.e-40 + 0.)) __builtin_abort ();; }
void convert_244 (void) { ; sd = -8.e-44df; df = sd; if (df < (-8.e-44 - 0.) || df > (-8.e-44 + 0.)) __builtin_abort ();; }
void convert_245 (void) { ; sd = -9.e-44df; df = sd; if (df < (-9.e-44 - 0.) || df > (-9.e-44 + 0.)) __builtin_abort ();; }
void convert_246 (void) { ; sd = -8.e-46df; df = sd; if (df < (-8.e-46 - 0.) || df > (-8.e-46 + 0.)) __builtin_abort ();; }
void convert_247 (void) { ; sd = -7.e-46df; df = sd; if (df < (-7.e-46 - 0.) || df > (-7.e-46 + 0.)) __builtin_abort ();; }

int
main ()
{
  convert_111 ();
  convert_112 ();
  convert_113 ();

  convert_121 ();
  convert_122 ();

  convert_131 ();
  convert_132 ();

  convert_141 ();
  convert_142 ();

  convert_211 ();
  convert_212 ();
  convert_213 ();
  convert_214 ();
  convert_215 ();
  convert_216 ();
  convert_217 ();

  convert_221 ();
  convert_222 ();
  convert_223 ();
  convert_224 ();
  convert_225 ();
  convert_226 ();
  convert_227 ();

  convert_231 ();
  convert_232 ();
  convert_233 ();
  convert_234 ();
  convert_235 ();
  convert_236 ();
  convert_237 ();

  convert_241 ();
  convert_242 ();
  convert_243 ();
  convert_244 ();
  convert_245 ();
  convert_246 ();
  convert_247 ();

  return 0;
}
