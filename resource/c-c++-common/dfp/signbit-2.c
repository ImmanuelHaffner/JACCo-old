int failures;

volatile _Decimal32 sd = 2.3df;
volatile _Decimal64 dd = -4.5dd;
volatile _Decimal128 tf = 5.3dl;
volatile float f = 1.2f;
volatile double d = -7.8;
volatile long double ld = 3.4L;

extern int signbitf (float);
extern int signbit (double);
extern int signbitl (long double);
extern int signbitd32 (_Decimal32);
extern int signbitd64 (_Decimal64);
extern int signbitd128 (_Decimal128);

int
main ()
{
  if (signbitf (f) != 0) __builtin_abort ();
  if (signbit (d) == 0) __builtin_abort ();
  if (signbitl (ld) != 0) __builtin_abort ();
  if (signbitd32 (sd) != 0) __builtin_abort ();
  if (signbitd64 (dd) == 0) __builtin_abort ();
  if (signbitd128 (tf) != 0) __builtin_abort ();

  return 0;
}
