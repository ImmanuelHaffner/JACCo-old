



int failures;
volatile _Decimal32 sd;
volatile _Decimal64 dd;
volatile _Decimal128 td;

int
main ()
{
  sd = 1.9df; if ((__builtin_signbitd32 (sd) != 0) != 0) __builtin_abort ();
  sd = -5.3df; if ((__builtin_signbitd32 (sd) != 0) != 1) __builtin_abort ();
  sd = 0.0df; if ((__builtin_signbitd32 (sd) != 0) != 0) __builtin_abort ();
  sd = -0.0df; if ((__builtin_signbitd32 (sd) != 0) != 1) __builtin_abort ();

  dd = 1.9dd; if ((__builtin_signbitd64 (dd) != 0) != 0) __builtin_abort ();
  dd = -5.3dd; if ((__builtin_signbitd64 (dd) != 0) != 1) __builtin_abort ();
  dd = 0.0dd; if ((__builtin_signbitd64 (dd) != 0) != 0) __builtin_abort ();
  dd = -0.0dd; if ((__builtin_signbitd64 (dd) != 0) != 1) __builtin_abort ();

  td = 1.9dl; if ((__builtin_signbitd128 (td) != 0) != 0) __builtin_abort ();
  td = -5.3dl; if ((__builtin_signbitd128 (td) != 0) != 1) __builtin_abort ();
  td = 0.0dl; if ((__builtin_signbitd128 (td) != 0) != 0) __builtin_abort ();
  td = -0.0dl; if ((__builtin_signbitd128 (td) != 0) != 1) __builtin_abort ();

  return 0;
}
