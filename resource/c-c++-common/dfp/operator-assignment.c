




int failures;
int
main ()
{
  _Decimal32 d32 = 1.23456df, d32a = 1.2df;
  _Decimal64 d64 = 23.456789dd, d64a = 2.8dd;
  _Decimal128 d128 = 345.67890123456789dl, d128a = 4.7dl;

  { _Decimal32 d = d32; if (( d += 1 )!= (d32 + 1)) __builtin_abort ();; d = d32; if (( d += 0 )!= d32) __builtin_abort ();; d = d32; if (( d += (-1) )!= (d32 - 1)) __builtin_abort ();; d = d32; if (( d += d32a )!= (d32 + d32a)) __builtin_abort ();; d = d32; if (( d += d64a )!= (d32 + d64a)) __builtin_abort ();; d = d32; if (( d += d128a )!= (d32 + d128a)) __builtin_abort ();; d = d32; if (( d += (_Decimal32)1.1 )!= (d32 + (_Decimal32)1.1)) __builtin_abort ();; d = d32; if (( d += (_Decimal32)2.2f )!= (d32 + (_Decimal32)2.2f)) __builtin_abort ();; d = d32; if (( d -= 1 )!= (d32 - 1)) __builtin_abort ();; d = d32; if (( d -= 0 )!= d32) __builtin_abort ();; d = d32; if (( d -= (-1) )!= (d32 + 1)) __builtin_abort ();; d = d32; if (( d -= d32a )!= d32-d32a) __builtin_abort ();; d = d32; if (( d -= d64a )!= d32-d64a) __builtin_abort ();; d = d32; if (( d -= d128a )!= d32-d128a) __builtin_abort ();; };
  { _Decimal64 d = d64; if (( d += 1 )!= (d64 + 1)) __builtin_abort ();; d = d64; if (( d += 0 )!= d64) __builtin_abort ();; d = d64; if (( d += (-1) )!= (d64 - 1)) __builtin_abort ();; d = d64; if (( d += d32a )!= (d64 + d32a)) __builtin_abort ();; d = d64; if (( d += d64a )!= (d64 + d64a)) __builtin_abort ();; d = d64; if (( d += d128a )!= (d64 + d128a)) __builtin_abort ();; d = d64; if (( d += (_Decimal64)1.1 )!= (d64 + (_Decimal64)1.1)) __builtin_abort ();; d = d64; if (( d += (_Decimal64)2.2f )!= (d64 + (_Decimal64)2.2f)) __builtin_abort ();; d = d64; if (( d -= 1 )!= (d64 - 1)) __builtin_abort ();; d = d64; if (( d -= 0 )!= d64) __builtin_abort ();; d = d64; if (( d -= (-1) )!= (d64 + 1)) __builtin_abort ();; d = d64; if (( d -= d32a )!= d64-d32a) __builtin_abort ();; d = d64; if (( d -= d64a )!= d64-d64a) __builtin_abort ();; d = d64; if (( d -= d128a )!= d64-d128a) __builtin_abort ();; };
  { _Decimal128 d = d128; if (( d += 1 )!= (d128 + 1)) __builtin_abort ();; d = d128; if (( d += 0 )!= d128) __builtin_abort ();; d = d128; if (( d += (-1) )!= (d128 - 1)) __builtin_abort ();; d = d128; if (( d += d32a )!= (d128 + d32a)) __builtin_abort ();; d = d128; if (( d += d64a )!= (d128 + d64a)) __builtin_abort ();; d = d128; if (( d += d128a )!= (d128 + d128a)) __builtin_abort ();; d = d128; if (( d += (_Decimal128)1.1 )!= (d128 + (_Decimal128)1.1)) __builtin_abort ();; d = d128; if (( d += (_Decimal128)2.2f )!= (d128 + (_Decimal128)2.2f)) __builtin_abort ();; d = d128; if (( d -= 1 )!= (d128 - 1)) __builtin_abort ();; d = d128; if (( d -= 0 )!= d128) __builtin_abort ();; d = d128; if (( d -= (-1) )!= (d128 + 1)) __builtin_abort ();; d = d128; if (( d -= d32a )!= d128-d32a) __builtin_abort ();; d = d128; if (( d -= d64a )!= d128-d64a) __builtin_abort ();; d = d128; if (( d -= d128a )!= d128-d128a) __builtin_abort ();; };

  return 0;
}
