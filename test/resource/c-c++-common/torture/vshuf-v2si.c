
typedef unsigned int V __attribute__((vector_size(8)));
typedef V VI;




struct S
{
  V in;
  VI mask;
  V out;
};

struct S tests[] = {
  { { 0x11121314, 0x21222324 }, { 0, 1 }, { 0x11121314, 0x21222324 } },
  { { 0x11121314, 0x21222324 }, { -16, -1 }, { 0x11121314, 0x21222324 } },
  { { 0x11121314, 0x21222324 }, { 1, 0 }, { 0x21222324, 0x11121314 } },
  { { 0x11121314, 0x21222324 }, { 0, 0 }, { 0x11121314, 0x11121314 } },
  { { 0xd1d2d3d4, 0xe1e2e3e4 }, { 1, 1 }, { 0xe1e2e3e4, 0xe1e2e3e4 } },
  { { 0xd1d2d3d4, 0xe1e2e3e4 }, { 1, 0 }, { 0xe1e2e3e4, 0xd1d2d3d4 } },
};

struct S2
{
  V in1, in2;
  VI mask;
  V out;
};

struct S2 tests2[] = {
  { { 0x11121314, 0x21222324 }, { 0xd1d2d3d4, 0xe1e2e3e4 }, { 0, 1 }, { 0x11121314, 0x21222324 } },
  { { 0x11121314, 0x21222324 }, { 0xd1d2d3d4, 0xe1e2e3e4 }, { 2, 3 }, { 0xd1d2d3d4, 0xe1e2e3e4 } },
  { { 0x11121314, 0x21222324 }, { 0xd1d2d3d4, 0xe1e2e3e4 }, { 0, 2 }, { 0x11121314, 0xd1d2d3d4 } },
  { { 0x11121314, 0x21222324 }, { 0xd1d2d3d4, 0xe1e2e3e4 }, { 2, 1 }, { 0xd1d2d3d4, 0x21222324 } },
  { { 0x11121314, 0x21222324 }, { 0xd1d2d3d4, 0xe1e2e3e4 }, { 3, 0 }, { 0xe1e2e3e4, 0x11121314 } },
  { { 0x11121314, 0x21222324 }, { 0xd1d2d3d4, 0xe1e2e3e4 }, { 0, 0 }, { 0x11121314, 0x11121314 } },
  { { 0x11121314, 0x21222324 }, { 0xd1d2d3d4, 0xe1e2e3e4 }, { 3, 3 }, { 0xe1e2e3e4, 0xe1e2e3e4 } },
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
