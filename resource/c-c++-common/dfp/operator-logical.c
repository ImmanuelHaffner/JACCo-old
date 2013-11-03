



int failures;
int
main ()
{
  _Decimal32 d32;
  _Decimal64 d64;
  _Decimal128 d128;



  do { d32 = 1.0; do { if (( (1) || (d32) )!= 1) __builtin_abort (); } while (0); do { if (( (0) || (d32) )!= 1) __builtin_abort (); } while (0); do { if (( (d32) || (1) )!= 1) __builtin_abort (); } while (0); do { if (( (d32) || (0) )!= 1) __builtin_abort (); } while (0); d32 = 0.0; do { if (( (1) || (d32) )!= 1) __builtin_abort (); } while (0); do { if (( (0) || (d32) )!= 0) __builtin_abort (); } while (0); do { if (( (d32) || (1) )!= 1) __builtin_abort (); } while (0); do { if (( (d32) || (0) )!= 0) __builtin_abort (); } while (0); } while (0);
  do { d32 = 1.0; do { if (( (1) && (d32) )!= 1) __builtin_abort (); } while (0); do { if (( (0) && (d32) )!= 0) __builtin_abort (); } while (0); do { if (( (d32) && (1) )!= 1) __builtin_abort (); } while (0); do { if (( (d32) && (0) )!= 0) __builtin_abort (); } while (0); d32 = 0.0; do { if (( (1) && (d32) )!= 0) __builtin_abort (); } while (0); do { if (( (0) && (d32) )!= 0) __builtin_abort (); } while (0); do { if (( (d32) && (1) )!= 0) __builtin_abort (); } while (0); do { if (( (d32) && (0) )!= 0) __builtin_abort (); } while (0); } while (0);

  do { d64 = 1.0; do { if (( (1) || (d64) )!= 1) __builtin_abort (); } while (0); do { if (( (0) || (d64) )!= 1) __builtin_abort (); } while (0); do { if (( (d64) || (1) )!= 1) __builtin_abort (); } while (0); do { if (( (d64) || (0) )!= 1) __builtin_abort (); } while (0); d64 = 0.0; do { if (( (1) || (d64) )!= 1) __builtin_abort (); } while (0); do { if (( (0) || (d64) )!= 0) __builtin_abort (); } while (0); do { if (( (d64) || (1) )!= 1) __builtin_abort (); } while (0); do { if (( (d64) || (0) )!= 0) __builtin_abort (); } while (0); } while (0);
  do { d64 = 1.0; do { if (( (1) && (d64) )!= 1) __builtin_abort (); } while (0); do { if (( (0) && (d64) )!= 0) __builtin_abort (); } while (0); do { if (( (d64) && (1) )!= 1) __builtin_abort (); } while (0); do { if (( (d64) && (0) )!= 0) __builtin_abort (); } while (0); d64 = 0.0; do { if (( (1) && (d64) )!= 0) __builtin_abort (); } while (0); do { if (( (0) && (d64) )!= 0) __builtin_abort (); } while (0); do { if (( (d64) && (1) )!= 0) __builtin_abort (); } while (0); do { if (( (d64) && (0) )!= 0) __builtin_abort (); } while (0); } while (0);

  do { d128 = 1.0; do { if (( (1) || (d128) )!= 1) __builtin_abort (); } while (0); do { if (( (0) || (d128) )!= 1) __builtin_abort (); } while (0); do { if (( (d128) || (1) )!= 1) __builtin_abort (); } while (0); do { if (( (d128) || (0) )!= 1) __builtin_abort (); } while (0); d128 = 0.0; do { if (( (1) || (d128) )!= 1) __builtin_abort (); } while (0); do { if (( (0) || (d128) )!= 0) __builtin_abort (); } while (0); do { if (( (d128) || (1) )!= 1) __builtin_abort (); } while (0); do { if (( (d128) || (0) )!= 0) __builtin_abort (); } while (0); } while (0);
  do { d128 = 1.0; do { if (( (1) && (d128) )!= 1) __builtin_abort (); } while (0); do { if (( (0) && (d128) )!= 0) __builtin_abort (); } while (0); do { if (( (d128) && (1) )!= 1) __builtin_abort (); } while (0); do { if (( (d128) && (0) )!= 0) __builtin_abort (); } while (0); d128 = 0.0; do { if (( (1) && (d128) )!= 0) __builtin_abort (); } while (0); do { if (( (0) && (d128) )!= 0) __builtin_abort (); } while (0); do { if (( (d128) && (1) )!= 0) __builtin_abort (); } while (0); do { if (( (d128) && (0) )!= 0) __builtin_abort (); } while (0); } while (0);

  return 0;
}
