



int failures;
typedef union {
  _Decimal32 d;
  unsigned int i;
} u32;

typedef union {
  _Decimal64 d;
  unsigned int i[2];
} u64;

typedef union {
  _Decimal128 d;
  unsigned int i[4];
} u128;

volatile u32 p32_1;
volatile u32 p32_1_0;
volatile u32 p32_2_0;
volatile u32 m32_1;
volatile u32 m32_1_0;
volatile u32 m32_2_0;
volatile u32 a32;

volatile u64 p64_1;
volatile u64 p64_1_0;
volatile u64 p64_2_0;
volatile u64 m64_1;
volatile u64 m64_1_0;
volatile u64 m64_2_0;
volatile u64 a64;

volatile u128 p128_1;
volatile u128 p128_1_0;
volatile u128 p128_2_0;
volatile u128 m128_1;
volatile u128 m128_1_0;
volatile u128 m128_2_0;
volatile u128 a128;

void
init32 (void)
{
  p32_1.d = 1.DF;
  p32_1_0.d = 1.0DF;
  p32_2_0.d = 2.0DF;
  m32_1.d = -1.DF;
  m32_1_0.d = -1.0DF;
  m32_2_0.d = -2.0DF;
}

void
init64 (void)
{
  p64_1.d = 1.DD;
  p64_1_0.d = 1.0DD;
  p64_2_0.d = 2.0DD;
  m64_1.d = -1.DD;
  m64_1_0.d = -1.0DD;
  m64_2_0.d = -2.0DD;
}

void
init128 (void)
{
  p128_1.d = 1.DL;
  p128_1_0.d = 1.0DL;
  p128_2_0.d = 2.0DL;
  m128_1.d = -1.DL;
  m128_1_0.d = -1.0DL;
  m128_2_0.d = -2.0DL;
}

void
doit32 (void)
{



  a32.d = p32_2_0.d * p32_1.d;
  if (! (a32.i == p32_2_0.i))
    __builtin_abort ();

  a32.d = p32_2_0.d * 1.DF;
  if (! (a32.i == p32_2_0.i))
    __builtin_abort ();

  a32.d = p32_2_0.d * m32_1.d;
  if (! (a32.i == m32_2_0.i))
    __builtin_abort ();

  a32.d = p32_2_0.d * -1.DF;
  if (! (a32.i == m32_2_0.i))
    __builtin_abort ();




  a32.d = p32_2_0.d * p32_1_0.d;
  if (a32.i == p32_2_0.i)
    __builtin_abort ();

  a32.d = p32_2_0.d * 1.0DF;
  if (a32.i == p32_2_0.i)
    __builtin_abort ();

  a32.d = p32_2_0.d * m32_1_0.d;
  if (a32.i == m32_2_0.i)
    __builtin_abort ();

  a32.d = p32_2_0.d * -1.0DF;
  if (a32.i == m32_2_0.i)
    __builtin_abort ();
}

void
doit64 (void)
{



  a64.d = p64_2_0.d * p64_1.d;
  if (! (a64.i[0] == p64_2_0.i[0] && a64.i[1] == p64_2_0.i[1]))
    __builtin_abort ();

  a64.d = p64_2_0.d * 1.DD;
  if (! (a64.i[0] == p64_2_0.i[0] && a64.i[1] == p64_2_0.i[1]))
    __builtin_abort ();

  a64.d = p64_2_0.d * m64_1.d;
  if (! (a64.i[0] == m64_2_0.i[0] && a64.i[1] == m64_2_0.i[1]))
    __builtin_abort ();

  a64.d = p64_2_0.d * -1.DD;
  if (! (a64.i[0] == m64_2_0.i[0] && a64.i[1] == m64_2_0.i[1]))
    __builtin_abort ();




  a64.d = p64_2_0.d * p64_1_0.d;
  if (a64.i[0] == p64_2_0.i[0] && a64.i[1] == p64_2_0.i[1])
    __builtin_abort ();

  a64.d = p64_2_0.d * 1.0DD;
  if (a64.i[0] == p64_2_0.i[0] && a64.i[1] == p64_2_0.i[1])
    __builtin_abort ();

  a64.d = p64_2_0.d * m64_1_0.d;
  if (a64.i[0] == m64_2_0.i[0] && a64.i[1] == m64_2_0.i[1])
    __builtin_abort ();

  a64.d = p64_2_0.d * -1.0DD;
  if (a64.i[0] == m64_2_0.i[0] && a64.i[1] == m64_2_0.i[1])
    __builtin_abort ();
}

void
doit128 (void)
{



  a128.d = p128_2_0.d * p128_1_0.d;
  if (a128.i[0] == p128_2_0.i[0] && a128.i[1] == p128_2_0.i[1] && a128.i[2] == p128_2_0.i[2] && a128.i[3] == p128_2_0.i[3])
    __builtin_abort ();

  a128.d = p128_2_0.d * 1.0DL;
  if (a128.i[0] == p128_2_0.i[0] && a128.i[1] == p128_2_0.i[1] && a128.i[2] == p128_2_0.i[2] && a128.i[3] == p128_2_0.i[3])
    __builtin_abort ();

  a128.d = p128_2_0.d * m128_1_0.d;
  if (a128.i[0] == m128_2_0.i[0] && a128.i[1] == m128_2_0.i[1] && a128.i[2] == m128_2_0.i[2] && a128.i[3] == m128_2_0.i[3])
    __builtin_abort ();

  a128.d = p128_2_0.d * -1.0DL;
  if (a128.i[0] == m128_2_0.i[0] && a128.i[1] == m128_2_0.i[1] && a128.i[2] == m128_2_0.i[2] && a128.i[3] == m128_2_0.i[3])
    __builtin_abort ();




  a128.d = p128_2_0.d * p128_1.d;
  if (! (a128.i[0] == p128_2_0.i[0] && a128.i[1] == p128_2_0.i[1] && a128.i[2] == p128_2_0.i[2] && a128.i[3] == p128_2_0.i[3]))
    __builtin_abort ();

  a128.d = p128_2_0.d * 1.DL;
  if (! (a128.i[0] == p128_2_0.i[0] && a128.i[1] == p128_2_0.i[1] && a128.i[2] == p128_2_0.i[2] && a128.i[3] == p128_2_0.i[3]))
    __builtin_abort ();

  a128.d = p128_2_0.d * m128_1.d;
  if (! (a128.i[0] == m128_2_0.i[0] && a128.i[1] == m128_2_0.i[1] && a128.i[2] == m128_2_0.i[2] && a128.i[3] == m128_2_0.i[3]))
    __builtin_abort ();

  a128.d = p128_2_0.d * -1.DL;
  if (! (a128.i[0] == m128_2_0.i[0] && a128.i[1] == m128_2_0.i[1] && a128.i[2] == m128_2_0.i[2] && a128.i[3] == m128_2_0.i[3]))
    __builtin_abort ();
}

int
main (void)
{
  init32 ();
  init64 ();
  init128 ();

  doit32 ();
  doit64 ();
  doit128 ();

  return 0;
}
