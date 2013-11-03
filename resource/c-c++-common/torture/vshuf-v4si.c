
typedef unsigned int V __attribute__((vector_size(16)));
typedef V VI;




struct S
{
  V in;
  VI mask;
  V out;
};

struct S tests[] = {
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 0, 1, 2, 3 }, { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, },
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 0+1*4, 1+2*4, 2+3*4, 3+4*4 }, { 0x11121314, 0x21222324, 0x31323334, 0x41424344 } },
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 3, 2, 1, 0 }, { 0x41424344, 0x31323334, 0x21222324, 0x11121314 } },
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 0, 3, 2, 1 }, { 0x11121314, 0x41424344, 0x31323334, 0x21222324 } },
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 0, 2, 1, 3 }, { 0x11121314, 0x31323334, 0x21222324, 0x41424344 } },
  { { 0xc1c2c3c4, 0xd1d2d3d4, 0xe1e2e3e4, 0xf1f2f3f4 }, { 3, 1, 2, 0 }, { 0xf1f2f3f4, 0xd1d2d3d4, 0xe1e2e3e4, 0xc1c2c3c4 } },
  { { 0xc1c2c3c4, 0xd1d2d3d4, 0xe1e2e3e4, 0xf1f2f3f4 }, { 0, 0, 0, 0 }, { 0xc1c2c3c4, 0xc1c2c3c4, 0xc1c2c3c4, 0xc1c2c3c4 } },
  { { 0xc1c2c3c4, 0xd1d2d3d4, 0xe1e2e3e4, 0xf1f2f3f4 }, { 1, 2, 1, 2 }, { 0xd1d2d3d4, 0xe1e2e3e4, 0xd1d2d3d4, 0xe1e2e3e4 } },
};

struct S2
{
  V in1, in2;
  VI mask;
  V out;
};

struct S2 tests2[] = {
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 0xc1c2c3c4, 0xd1d2d3d4, 0xe1e2e3e4, 0xf1f2f3f4 }, { 0, 1, 2, 3 }, { 0x11121314, 0x21222324, 0x31323334, 0x41424344 } },
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 0xc1c2c3c4, 0xd1d2d3d4, 0xe1e2e3e4, 0xf1f2f3f4 }, { 4, 5, 6, 7 }, { 0xc1c2c3c4, 0xd1d2d3d4, 0xe1e2e3e4, 0xf1f2f3f4 } },
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 0xc1c2c3c4, 0xd1d2d3d4, 0xe1e2e3e4, 0xf1f2f3f4 }, { 0, 4, 1, 5 }, { 0x11121314, 0xc1c2c3c4, 0x21222324, 0xd1d2d3d4 } },
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 0xc1c2c3c4, 0xd1d2d3d4, 0xe1e2e3e4, 0xf1f2f3f4 }, { 0, 7, 4, 3 }, { 0x11121314, 0xf1f2f3f4, 0xc1c2c3c4, 0x41424344 } },
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 0xc1c2c3c4, 0xd1d2d3d4, 0xe1e2e3e4, 0xf1f2f3f4 }, { 0, 0, 0, 0 }, { 0x11121314, 0x11121314, 0x11121314, 0x11121314 } },
  { { 0x11121314, 0x21222324, 0x31323334, 0x41424344 }, { 0xc1c2c3c4, 0xd1d2d3d4, 0xe1e2e3e4, 0xf1f2f3f4 }, { 7, 7, 7, 7 }, { 0xf1f2f3f4, 0xf1f2f3f4, 0xf1f2f3f4, 0xf1f2f3f4 } },
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
