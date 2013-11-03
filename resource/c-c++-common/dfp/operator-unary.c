

int failures;
int
main ()
{

  do { _Decimal32 in_de_d32 = 0.0DF; if (in_de_d32++) __builtin_abort (); if (--in_de_d32) __builtin_abort (); if (++in_de_d32 == 0.0DF) __builtin_abort (); if (in_de_d32-- == 0.0DF) __builtin_abort (); } while(0);
  do { _Decimal64 in_de_d64 = 0.0DD; if (in_de_d64++) __builtin_abort (); if (--in_de_d64) __builtin_abort (); if (++in_de_d64 == 0.0DD) __builtin_abort (); if (in_de_d64-- == 0.0DD) __builtin_abort (); } while(0);
  do { _Decimal128 in_de_d128 = 0.0DL; if (in_de_d128++) __builtin_abort (); if (--in_de_d128) __builtin_abort (); if (++in_de_d128 == 0.0DL) __builtin_abort (); if (in_de_d128-- == 0.0DL) __builtin_abort (); } while(0);


  do { _Decimal32 unary_d32 = 1.0DF; _Decimal32* unary_dp32; unary_dp32 = &(unary_d32); unary_d32 = *(unary_dp32); unary_d32 = -unary_d32; if (unary_d32 != -1.0DF) __builtin_abort (); unary_d32 = +unary_d32; if (unary_d32 != -1.0DF) __builtin_abort (); if (!unary_d32) __builtin_abort (); } while (0);
  do { _Decimal64 unary_d64 = 1.0DD; _Decimal64* unary_dp64; unary_dp64 = &(unary_d64); unary_d64 = *(unary_dp64); unary_d64 = -unary_d64; if (unary_d64 != -1.0DD) __builtin_abort (); unary_d64 = +unary_d64; if (unary_d64 != -1.0DD) __builtin_abort (); if (!unary_d64) __builtin_abort (); } while (0);
  do { _Decimal128 unary_d128 = 1.0DL; _Decimal128* unary_dp128; unary_dp128 = &(unary_d128); unary_d128 = *(unary_dp128); unary_d128 = -unary_d128; if (unary_d128 != -1.0DL) __builtin_abort (); unary_d128 = +unary_d128; if (unary_d128 != -1.0DL) __builtin_abort (); if (!unary_d128) __builtin_abort (); } while (0);


  if (- +0.df != -0.df) __builtin_abort ();
  if (+ -0.df != -0.df) __builtin_abort ();
  if (- -0.df != +0.df) __builtin_abort ();

  return 0;
}
