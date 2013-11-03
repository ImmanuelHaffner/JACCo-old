
typedef unsigned long long V __attribute__((vector_size(16)));
typedef V VI;




struct S
{
  V in;
  VI mask;
  V out;
};

struct S tests[] = {
  { { 0x1112131415161718, 0x2122232425262728 }, { 0, 1 }, { 0x1112131415161718, 0x2122232425262728 } },
  { { 0x1112131415161718, 0x2122232425262728 }, { -16, -1 }, { 0x1112131415161718, 0x2122232425262728 } },
  { { 0x1112131415161718, 0x2122232425262728 }, { 1, 0 }, { 0x2122232425262728, 0x1112131415161718 } },
  { { 0x1112131415161718, 0x2122232425262728 }, { 0, 0 }, { 0x1112131415161718, 0x1112131415161718 } },
  { { 0xc1c2c3c4c5c6c7c8, 0xd1d2d3d4d5d6d7d8 }, { 1, 1 }, { 0xd1d2d3d4d5d6d7d8, 0xd1d2d3d4d5d6d7d8 } },
  { { 0xc1c2c3c4c5c6c7c8, 0xd1d2d3d4d5d6d7d8 }, { 1, 0 }, { 0xd1d2d3d4d5d6d7d8, 0xc1c2c3c4c5c6c7c8 } },
};

struct S2
{
  V in1, in2;
  VI mask;
  V out;
};

struct S2 tests2[] = {
  { { 0x1112131415161718, 0x2122232425262728 }, { 0xc1c2c3c4c5c6c7c8, 0xd1d2d3d4d5d6d7d8 }, { 0, 1 }, { 0x1112131415161718, 0x2122232425262728 } },
  { { 0x1112131415161718, 0x2122232425262728 }, { 0xc1c2c3c4c5c6c7c8, 0xd1d2d3d4d5d6d7d8 }, { 2, 3 }, { 0xc1c2c3c4c5c6c7c8, 0xd1d2d3d4d5d6d7d8 } },
  { { 0x1112131415161718, 0x2122232425262728 }, { 0xc1c2c3c4c5c6c7c8, 0xd1d2d3d4d5d6d7d8 }, { 0, 2 }, { 0x1112131415161718, 0xc1c2c3c4c5c6c7c8 } },
  { { 0x1112131415161718, 0x2122232425262728 }, { 0xc1c2c3c4c5c6c7c8, 0xd1d2d3d4d5d6d7d8 }, { 2, 1 }, { 0xc1c2c3c4c5c6c7c8, 0x2122232425262728 } },
  { { 0x1112131415161718, 0x2122232425262728 }, { 0xc1c2c3c4c5c6c7c8, 0xd1d2d3d4d5d6d7d8 }, { 3, 0 }, { 0xd1d2d3d4d5d6d7d8, 0x1112131415161718 } },
  { { 0x1112131415161718, 0x2122232425262728 }, { 0xc1c2c3c4c5c6c7c8, 0xd1d2d3d4d5d6d7d8 }, { 0, 0 }, { 0x1112131415161718, 0x1112131415161718 } },
  { { 0x1112131415161718, 0x2122232425262728 }, { 0xc1c2c3c4c5c6c7c8, 0xd1d2d3d4d5d6d7d8 }, { 3, 3 }, { 0xd1d2d3d4d5d6d7d8, 0xd1d2d3d4d5d6d7d8 } },
};


extern void abort(void);

int main()
{

  int i;

  for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i)
    {
      V r = __builtin_shuffle(tests[i].in, tests[i].mask);
      if (__builtin_memcmp(&r, &tests[i].out, sizeof(V)) != 0)
 abort();
    }

  for (i = 0; i < sizeof(tests2)/sizeof(tests2[0]); ++i)
    {
      V r = __builtin_shuffle(tests2[i].in1, tests2[i].in2, tests2[i].mask);
      if (__builtin_memcmp(&r, &tests2[i].out, sizeof(V)) != 0)
 abort();
    }


  return 0;
}
