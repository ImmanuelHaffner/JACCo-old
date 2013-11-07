







extern



void abort (void);





unsigned int
f1 (unsigned int x, int y)
{
  return (x << y) | (x >> ((-y) & (8 * 4 - 1)));
}

unsigned int
f2 (unsigned int x, long int y)
{
  return (x << y) | (x >> ((-y) & (8 * 4 - 1)));
}

unsigned int
f3 (unsigned int x, int y __attribute__((unused)))
{
  return (x << 1) | (x >> ((-1) & (8 * 4 - 1)));
}

unsigned int
f4 (unsigned int x, int y __attribute__((unused)))
{
  return (x << ((-1) & (8 * 4 - 1))) | (x >> 1);
}

unsigned short int
f5 (unsigned short int x, int y)
{
  return (x << y) | (x >> ((-y) & (8 * 2 - 1)));
}

unsigned short int
f6 (unsigned short int x, long int y)
{
  return (x << y) | (x >> ((-y) & (8 * 2 - 1)));
}

unsigned char
f7 (unsigned char x, int y)
{
  return (x << y) | (x >> ((-y) & (8 - 1)));
}

unsigned char
f8 (unsigned char x, long int y)
{
  return (x << y) | (x >> ((-y) & (8 - 1)));
}

unsigned int
f9 (unsigned int x, int y)
{
  return (x << y) | (x >> ((-y) & (8 * sizeof (unsigned int) - 1)));
}

unsigned int
f10 (unsigned int x, long int y)
{
  return (x << y) | (x >> ((-y) & (8 * sizeof (unsigned int) - 1)));
}

unsigned int
f11 (unsigned int x, int y __attribute__((unused)))
{
  return (x << 1) | (x >> ((-1) & (8 * sizeof (unsigned int) - 1)));
}

unsigned int
f12 (unsigned int x, int y __attribute__((unused)))
{
  return (x << ((-1) & (8 * sizeof (unsigned int) - 1))) | (x >> 1);
}

unsigned short int
f13 (unsigned short int x, int y)
{
  return (x << y) | (x >> ((-y) & (8 * sizeof (unsigned short) - 1)));
}

unsigned short int
f14 (unsigned short int x, long int y)
{
  return (x << y) | (x >> ((-y) & (8 * sizeof (unsigned short) - 1)));
}

unsigned char
f15 (unsigned char x, int y)
{
  return (x << y) | (x >> ((-y) & (8 * sizeof (unsigned char) - 1)));
}

unsigned char
f16 (unsigned char x, long int y)
{
  return (x << y) | (x >> ((-y) & (8 * sizeof (unsigned char) - 1)));
}

unsigned int
f17 (unsigned int x, int y)
{
  return (x >> ((-y) & (8 * 4 - 1))) ^ (x << y);
}

unsigned int
f18 (unsigned int x, long int y)
{
  return (x >> ((-y) & (8 * 4 - 1))) ^ (x << y);
}

unsigned int
f19 (unsigned int x, int y __attribute__((unused)))
{
  return (x >> ((-1) & (8 * 4 - 1))) ^ (x << 1);
}

unsigned int
f20 (unsigned int x, int y __attribute__((unused)))
{
  return (x >> 1) ^ (x << ((-1) & (8 * 4 - 1)));
}

unsigned short int
f21 (unsigned short int x, int y)
{
  return (x >> ((-y) & (8 * 2 - 1))) ^ (x << y);
}

unsigned short int
f22 (unsigned short int x, long int y)
{
  return (x >> ((-y) & (8 * 2 - 1))) ^ (x << y);
}

unsigned char
f23 (unsigned char x, int y)
{
  return (x >> ((-y) & (8 - 1))) ^ (x << y);
}

unsigned char
f24 (unsigned char x, long int y)
{
  return (x >> ((-y) & (8 - 1))) ^ (x << y);
}

unsigned int
f25 (unsigned int x, int y)
{
  return (x >> ((-y) & (8 * sizeof (unsigned int) - 1))) ^ (x << y);
}

unsigned int
f26 (unsigned int x, long int y)
{
  return (x >> ((-y) & (8 * sizeof (unsigned int) - 1))) ^ (x << y);
}

unsigned int
f27 (unsigned int x, int y __attribute__((unused)))
{
  return (x >> ((-1) & (8 * sizeof (unsigned int) - 1))) ^ (x << 1);
}

unsigned int
f28 (unsigned int x, int y __attribute__((unused)))
{
  return (x >> 1) ^ (x << ((-1) & (8 * sizeof (unsigned int) - 1)));
}

unsigned short int
f29 (unsigned short int x, int y)
{
  return (x >> ((-y) & (8 * sizeof (unsigned short) - 1))) ^ (x << y);
}

unsigned short int
f30 (unsigned short int x, long int y)
{
  return (x >> ((-y) & (8 * sizeof (unsigned short) - 1))) ^ (x << y);
}

unsigned char
f31 (unsigned char x, int y)
{
  return (x >> ((-y) & (8 * sizeof (unsigned char) - 1))) ^ (x << y);
}

unsigned char
f32 (unsigned char x, long int y)
{
  return (x >> ((-y) & (8 * sizeof (unsigned char) - 1))) ^ (x << y);
}

unsigned int
f33 (unsigned int x, int y)
{
  return (x >> y) | (x << ((-y) & (8 * 4 - 1)));
}

unsigned int
f34 (unsigned int x, long int y)
{
  return (x >> y) | (x << ((-y) & (8 * 4 - 1)));
}

unsigned int
f35 (unsigned int x, int y __attribute__((unused)))
{
  return (x >> 1) | (x << ((-1) & (8 * 4 - 1)));
}

unsigned int
f36 (unsigned int x, int y __attribute__((unused)))
{
  return (x >> ((-1) & (8 * 4 - 1))) | (x << 1);
}

unsigned short int
f37 (unsigned short int x, int y)
{
  return (x >> y) | (x << ((-y) & (8 * 2 - 1)));
}

unsigned short int
f38 (unsigned short int x, long int y)
{
  return (x >> y) | (x << ((-y) & (8 * 2 - 1)));
}

unsigned char
f39 (unsigned char x, int y)
{
  return (x >> y) | (x << ((-y) & (8 - 1)));
}

unsigned char
f40 (unsigned char x, long int y)
{
  return (x >> y) | (x << ((-y) & (8 - 1)));
}

unsigned int
f41 (unsigned int x, int y)
{
  return (x >> y) | (x << ((-y) & (8 * sizeof (unsigned int) - 1)));
}

unsigned int
f42 (unsigned int x, long int y)
{
  return (x >> y) | (x << ((-y) & (8 * sizeof (unsigned int) - 1)));
}

unsigned int
f43 (unsigned int x, int y __attribute__((unused)))
{
  return (x >> 1) | (x << ((-1) & (8 * sizeof (unsigned int) - 1)));
}

unsigned int
f44 (unsigned int x, int y __attribute__((unused)))
{
  return (x >> ((-1) & (8 * sizeof (unsigned int) - 1))) | (x << 1);
}

unsigned short int
f45 (unsigned short int x, int y)
{
  return (x >> y) | (x << ((-y) & (8 * sizeof (unsigned short) - 1)));
}

unsigned short int
f46 (unsigned short int x, long int y)
{
  return (x >> y) | (x << ((-y) & (8 * sizeof (unsigned short) - 1)));
}

unsigned char
f47 (unsigned char x, int y)
{
  return (x >> y) | (x << ((-y) & (8 * sizeof (unsigned char) - 1)));
}

unsigned char
f48 (unsigned char x, long int y)
{
  return (x >> y) | (x << ((-y) & (8 * sizeof (unsigned char) - 1)));
}

unsigned int
f49 (unsigned int x, int y)
{
  return (x << ((-y) & (8 * 4 - 1))) ^ (x >> y);
}

unsigned int
f50 (unsigned int x, long int y)
{
  return (x << ((-y) & (8 * 4 - 1))) ^ (x >> y);
}

unsigned int
f51 (unsigned int x, int y __attribute__((unused)))
{
  return (x << ((-1) & (8 * 4 - 1))) ^ (x >> 1);
}

unsigned int
f52 (unsigned int x, int y __attribute__((unused)))
{
  return (x << 1) ^ (x >> ((-1) & (8 * 4 - 1)));
}

unsigned short int
f53 (unsigned short int x, int y)
{
  return (x << ((-y) & (8 * 2 - 1))) ^ (x >> y);
}

unsigned short int
f54 (unsigned short int x, long int y)
{
  return (x << ((-y) & (8 * 2 - 1))) ^ (x >> y);
}

unsigned char
f55 (unsigned char x, int y)
{
  return (x << ((-y) & (8 - 1))) ^ (x >> y);
}

unsigned char
f56 (unsigned char x, long int y)
{
  return (x << ((-y) & (8 - 1))) ^ (x >> y);
}

unsigned int
f57 (unsigned int x, int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned int) - 1))) ^ (x >> y);
}

unsigned int
f58 (unsigned int x, long int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned int) - 1))) ^ (x >> y);
}

unsigned int
f59 (unsigned int x, int y __attribute__((unused)))
{
  return (x << ((-1) & (8 * sizeof (unsigned int) - 1))) ^ (x >> 1);
}

unsigned int
f60 (unsigned int x, int y __attribute__((unused)))
{
  return (x << 1) ^ (x >> ((-1) & (8 * sizeof (unsigned int) - 1)));
}

unsigned short int
f61 (unsigned short int x, int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned short) - 1))) ^ (x >> y);
}

unsigned short int
f62 (unsigned short int x, long int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned short) - 1))) ^ (x >> y);
}

unsigned char
f63 (unsigned char x, int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned char) - 1))) ^ (x >> y);
}

unsigned char
f64 (unsigned char x, long int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned char) - 1))) ^ (x >> y);
}

unsigned int
f65 (unsigned int x, int y)
{
  return (x << y) + (x >> ((-y) & (8 * 4 - 1)));
}

unsigned int
f66 (unsigned int x, long int y)
{
  return (x << y) + (x >> ((-y) & (8 * 4 - 1)));
}

unsigned int
f67 (unsigned int x, int y __attribute__((unused)))
{
  return (x << 1) + (x >> ((-1) & (8 * 4 - 1)));
}

unsigned int
f68 (unsigned int x, int y __attribute__((unused)))
{
  return (x << ((-1) & (8 * 4 - 1))) + (x >> 1);
}

unsigned short int
f69 (unsigned short int x, int y)
{
  return (x << y) + (x >> ((-y) & (8 * 2 - 1)));
}

unsigned short int
f70 (unsigned short int x, long int y)
{
  return (x << y) + (x >> ((-y) & (8 * 2 - 1)));
}

unsigned char
f71 (unsigned char x, int y)
{
  return (x << y) + (x >> ((-y) & (8 - 1)));
}

unsigned char
f72 (unsigned char x, long int y)
{
  return (x << y) + (x >> ((-y) & (8 - 1)));
}

unsigned int
f73 (unsigned int x, int y)
{
  return (x << y) + (x >> ((-y) & (8 * sizeof (unsigned int) - 1)));
}

unsigned int
f74 (unsigned int x, long int y)
{
  return (x << y) + (x >> ((-y) & (8 * sizeof (unsigned int) - 1)));
}

unsigned int
f75 (unsigned int x, int y __attribute__((unused)))
{
  return (x << 1) + (x >> ((-1) & (8 * sizeof (unsigned int) - 1)));
}

unsigned int
f76 (unsigned int x, int y __attribute__((unused)))
{
  return (x << ((-1) & (8 * sizeof (unsigned int) - 1))) + (x >> 1);
}

unsigned short int
f77 (unsigned short int x, int y)
{
  return (x << y) + (x >> ((-y) & (8 * sizeof (unsigned short) - 1)));
}

unsigned short int
f78 (unsigned short int x, long int y)
{
  return (x << y) + (x >> ((-y) & (8 * sizeof (unsigned short) - 1)));
}

unsigned char
f79 (unsigned char x, int y)
{
  return (x << y) + (x >> ((-y) & (8 * sizeof (unsigned char) - 1)));
}

unsigned char
f80 (unsigned char x, long int y)
{
  return (x << y) + (x >> ((-y) & (8 * sizeof (unsigned char) - 1)));
}

unsigned int
f81 (unsigned int x, int y)
{
  return (x << ((-y) & (8 * 4 - 1))) + (x >> y);
}

unsigned int
f82 (unsigned int x, long int y)
{
  return (x << ((-y) & (8 * 4 - 1))) + (x >> y);
}

unsigned int
f83 (unsigned int x, int y __attribute__((unused)))
{
  return (x << ((-1) & (8 * 4 - 1))) + (x >> 1);
}

unsigned int
f84 (unsigned int x, int y __attribute__((unused)))
{
  return (x << 1) + (x >> ((-1) & (8 * 4 - 1)));
}

unsigned short int
f85 (unsigned short int x, int y)
{
  return (x << ((-y) & (8 * 2 - 1))) + (x >> y);
}

unsigned short int
f86 (unsigned short int x, long int y)
{
  return (x << ((-y) & (8 * 2 - 1))) + (x >> y);
}

unsigned char
f87 (unsigned char x, int y)
{
  return (x << ((-y) & (8 - 1))) + (x >> y);
}

unsigned char
f88 (unsigned char x, long int y)
{
  return (x << ((-y) & (8 - 1))) + (x >> y);
}

unsigned int
f89 (unsigned int x, int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned int) - 1))) + (x >> y);
}

unsigned int
f90 (unsigned int x, long int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned int) - 1))) + (x >> y);
}

unsigned int
f91 (unsigned int x, int y __attribute__((unused)))
{
  return (x << ((-1) & (8 * sizeof (unsigned int) - 1))) + (x >> 1);
}

unsigned int
f92 (unsigned int x, int y __attribute__((unused)))
{
  return (x << 1) + (x >> ((-1) & (8 * sizeof (unsigned int) - 1)));
}

unsigned short int
f93 (unsigned short int x, int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned short) - 1))) + (x >> y);
}

unsigned short int
f94 (unsigned short int x, long int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned short) - 1))) + (x >> y);
}

unsigned char
f95 (unsigned char x, int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned char) - 1))) + (x >> y);
}

unsigned char
f96 (unsigned char x, long int y)
{
  return (x << ((-y) & (8 * sizeof (unsigned char) - 1))) + (x >> y);
}

unsigned int expected[] = {
0x91a2b3c0, 0x91a2b3c0, 0x2468acf0, 0x91a2b3c, 0xb3c2, 0xb3c2, 0xc3, 0xc3,
0x91a2b3c0, 0x91a2b3c0, 0x2468acf0, 0x91a2b3c, 0xb3c2, 0xb3c2, 0xc3, 0xc3,
0x91a2b3c0, 0x91a2b3c0, 0x2468acf0, 0x91a2b3c, 0xb3c2, 0xb3c2, 0xc3, 0xc3,
0x91a2b3c0, 0x91a2b3c0, 0x2468acf0, 0x91a2b3c, 0xb3c2, 0xb3c2, 0xc3, 0xc3,
0x2468acf, 0x2468acf, 0x91a2b3c, 0x2468acf0, 0xacf, 0xacf, 0xf, 0xf,
0x2468acf, 0x2468acf, 0x91a2b3c, 0x2468acf0, 0xacf, 0xacf, 0xf, 0xf,
0x2468acf, 0x2468acf, 0x91a2b3c, 0x2468acf0, 0xacf, 0xacf, 0xf, 0xf,
0x2468acf, 0x2468acf, 0x91a2b3c, 0x2468acf0, 0xacf, 0xacf, 0xf, 0xf,
0x91a2b3c0, 0x91a2b3c0, 0x2468acf0, 0x91a2b3c, 0xb3c2, 0xb3c2, 0xc3, 0xc3,
0x91a2b3c0, 0x91a2b3c0, 0x2468acf0, 0x91a2b3c, 0xb3c2, 0xb3c2, 0xc3, 0xc3,
0x2468acf, 0x2468acf, 0x91a2b3c, 0x2468acf0, 0xacf, 0xacf, 0xf, 0xf,
0x2468acf, 0x2468acf, 0x91a2b3c, 0x2468acf0, 0xacf, 0xacf, 0xf, 0xf };







__typeof (f1) f1 __attribute__((noinline, noclone)); __typeof (f2) f2 __attribute__((noinline, noclone)); __typeof (f3) f3 __attribute__((noinline, noclone)); __typeof (f4) f4 __attribute__((noinline, noclone)); __typeof (f5) f5 __attribute__((noinline, noclone)); __typeof (f6) f6 __attribute__((noinline, noclone)); __typeof (f7) f7 __attribute__((noinline, noclone)); __typeof (f8) f8 __attribute__((noinline, noclone)); __typeof (f9) f9 __attribute__((noinline, noclone)); __typeof (f10) f10 __attribute__((noinline, noclone)); __typeof (f11) f11 __attribute__((noinline, noclone)); __typeof (f12) f12 __attribute__((noinline, noclone)); __typeof (f13) f13 __attribute__((noinline, noclone)); __typeof (f14) f14 __attribute__((noinline, noclone)); __typeof (f15) f15 __attribute__((noinline, noclone)); __typeof (f16) f16 __attribute__((noinline, noclone)); __typeof (f17) f17 __attribute__((noinline, noclone)); __typeof (f18) f18 __attribute__((noinline, noclone)); __typeof (f19) f19 __attribute__((noinline, noclone)); __typeof (f20) f20 __attribute__((noinline, noclone)); __typeof (f21) f21 __attribute__((noinline, noclone)); __typeof (f22) f22 __attribute__((noinline, noclone)); __typeof (f23) f23 __attribute__((noinline, noclone)); __typeof (f24) f24 __attribute__((noinline, noclone)); __typeof (f25) f25 __attribute__((noinline, noclone)); __typeof (f26) f26 __attribute__((noinline, noclone)); __typeof (f27) f27 __attribute__((noinline, noclone)); __typeof (f28) f28 __attribute__((noinline, noclone)); __typeof (f29) f29 __attribute__((noinline, noclone)); __typeof (f30) f30 __attribute__((noinline, noclone)); __typeof (f31) f31 __attribute__((noinline, noclone)); __typeof (f32) f32 __attribute__((noinline, noclone)); __typeof (f33) f33 __attribute__((noinline, noclone)); __typeof (f34) f34 __attribute__((noinline, noclone)); __typeof (f35) f35 __attribute__((noinline, noclone)); __typeof (f36) f36 __attribute__((noinline, noclone)); __typeof (f37) f37 __attribute__((noinline, noclone)); __typeof (f38) f38 __attribute__((noinline, noclone)); __typeof (f39) f39 __attribute__((noinline, noclone)); __typeof (f40) f40 __attribute__((noinline, noclone)); __typeof (f41) f41 __attribute__((noinline, noclone)); __typeof (f42) f42 __attribute__((noinline, noclone)); __typeof (f43) f43 __attribute__((noinline, noclone)); __typeof (f44) f44 __attribute__((noinline, noclone)); __typeof (f45) f45 __attribute__((noinline, noclone)); __typeof (f46) f46 __attribute__((noinline, noclone)); __typeof (f47) f47 __attribute__((noinline, noclone)); __typeof (f48) f48 __attribute__((noinline, noclone)); __typeof (f49) f49 __attribute__((noinline, noclone)); __typeof (f50) f50 __attribute__((noinline, noclone)); __typeof (f51) f51 __attribute__((noinline, noclone)); __typeof (f52) f52 __attribute__((noinline, noclone)); __typeof (f53) f53 __attribute__((noinline, noclone)); __typeof (f54) f54 __attribute__((noinline, noclone)); __typeof (f55) f55 __attribute__((noinline, noclone)); __typeof (f56) f56 __attribute__((noinline, noclone)); __typeof (f57) f57 __attribute__((noinline, noclone)); __typeof (f58) f58 __attribute__((noinline, noclone)); __typeof (f59) f59 __attribute__((noinline, noclone)); __typeof (f60) f60 __attribute__((noinline, noclone)); __typeof (f61) f61 __attribute__((noinline, noclone)); __typeof (f62) f62 __attribute__((noinline, noclone)); __typeof (f63) f63 __attribute__((noinline, noclone)); __typeof (f64) f64 __attribute__((noinline, noclone)); __typeof (f65) f65 __attribute__((noinline, noclone)); __typeof (f66) f66 __attribute__((noinline, noclone)); __typeof (f67) f67 __attribute__((noinline, noclone)); __typeof (f68) f68 __attribute__((noinline, noclone)); __typeof (f69) f69 __attribute__((noinline, noclone)); __typeof (f70) f70 __attribute__((noinline, noclone)); __typeof (f71) f71 __attribute__((noinline, noclone)); __typeof (f72) f72 __attribute__((noinline, noclone)); __typeof (f73) f73 __attribute__((noinline, noclone)); __typeof (f74) f74 __attribute__((noinline, noclone)); __typeof (f75) f75 __attribute__((noinline, noclone)); __typeof (f76) f76 __attribute__((noinline, noclone)); __typeof (f77) f77 __attribute__((noinline, noclone)); __typeof (f78) f78 __attribute__((noinline, noclone)); __typeof (f79) f79 __attribute__((noinline, noclone)); __typeof (f80) f80 __attribute__((noinline, noclone)); __typeof (f81) f81 __attribute__((noinline, noclone)); __typeof (f82) f82 __attribute__((noinline, noclone)); __typeof (f83) f83 __attribute__((noinline, noclone)); __typeof (f84) f84 __attribute__((noinline, noclone)); __typeof (f85) f85 __attribute__((noinline, noclone)); __typeof (f86) f86 __attribute__((noinline, noclone)); __typeof (f87) f87 __attribute__((noinline, noclone)); __typeof (f88) f88 __attribute__((noinline, noclone)); __typeof (f89) f89 __attribute__((noinline, noclone)); __typeof (f90) f90 __attribute__((noinline, noclone)); __typeof (f91) f91 __attribute__((noinline, noclone)); __typeof (f92) f92 __attribute__((noinline, noclone)); __typeof (f93) f93 __attribute__((noinline, noclone)); __typeof (f94) f94 __attribute__((noinline, noclone)); __typeof (f95) f95 __attribute__((noinline, noclone)); __typeof (f96) f96 __attribute__((noinline, noclone));

int
main ()
{





  if ((unsigned int) f1 (0x12345678U, 3) != expected[1 - 1]) abort (); if ((unsigned int) f2 (0x12345678U, 3) != expected[2 - 1]) abort (); if ((unsigned int) f3 (0x12345678U, 3) != expected[3 - 1]) abort (); if ((unsigned int) f4 (0x12345678U, 3) != expected[4 - 1]) abort (); if ((unsigned int) f5 (0x12345678U, 3) != expected[5 - 1]) abort (); if ((unsigned int) f6 (0x12345678U, 3) != expected[6 - 1]) abort (); if ((unsigned int) f7 (0x12345678U, 3) != expected[7 - 1]) abort (); if ((unsigned int) f8 (0x12345678U, 3) != expected[8 - 1]) abort (); if ((unsigned int) f9 (0x12345678U, 3) != expected[9 - 1]) abort (); if ((unsigned int) f10 (0x12345678U, 3) != expected[10 - 1]) abort (); if ((unsigned int) f11 (0x12345678U, 3) != expected[11 - 1]) abort (); if ((unsigned int) f12 (0x12345678U, 3) != expected[12 - 1]) abort (); if ((unsigned int) f13 (0x12345678U, 3) != expected[13 - 1]) abort (); if ((unsigned int) f14 (0x12345678U, 3) != expected[14 - 1]) abort (); if ((unsigned int) f15 (0x12345678U, 3) != expected[15 - 1]) abort (); if ((unsigned int) f16 (0x12345678U, 3) != expected[16 - 1]) abort (); if ((unsigned int) f17 (0x12345678U, 3) != expected[17 - 1]) abort (); if ((unsigned int) f18 (0x12345678U, 3) != expected[18 - 1]) abort (); if ((unsigned int) f19 (0x12345678U, 3) != expected[19 - 1]) abort (); if ((unsigned int) f20 (0x12345678U, 3) != expected[20 - 1]) abort (); if ((unsigned int) f21 (0x12345678U, 3) != expected[21 - 1]) abort (); if ((unsigned int) f22 (0x12345678U, 3) != expected[22 - 1]) abort (); if ((unsigned int) f23 (0x12345678U, 3) != expected[23 - 1]) abort (); if ((unsigned int) f24 (0x12345678U, 3) != expected[24 - 1]) abort (); if ((unsigned int) f25 (0x12345678U, 3) != expected[25 - 1]) abort (); if ((unsigned int) f26 (0x12345678U, 3) != expected[26 - 1]) abort (); if ((unsigned int) f27 (0x12345678U, 3) != expected[27 - 1]) abort (); if ((unsigned int) f28 (0x12345678U, 3) != expected[28 - 1]) abort (); if ((unsigned int) f29 (0x12345678U, 3) != expected[29 - 1]) abort (); if ((unsigned int) f30 (0x12345678U, 3) != expected[30 - 1]) abort (); if ((unsigned int) f31 (0x12345678U, 3) != expected[31 - 1]) abort (); if ((unsigned int) f32 (0x12345678U, 3) != expected[32 - 1]) abort (); if ((unsigned int) f33 (0x12345678U, 3) != expected[33 - 1]) abort (); if ((unsigned int) f34 (0x12345678U, 3) != expected[34 - 1]) abort (); if ((unsigned int) f35 (0x12345678U, 3) != expected[35 - 1]) abort (); if ((unsigned int) f36 (0x12345678U, 3) != expected[36 - 1]) abort (); if ((unsigned int) f37 (0x12345678U, 3) != expected[37 - 1]) abort (); if ((unsigned int) f38 (0x12345678U, 3) != expected[38 - 1]) abort (); if ((unsigned int) f39 (0x12345678U, 3) != expected[39 - 1]) abort (); if ((unsigned int) f40 (0x12345678U, 3) != expected[40 - 1]) abort (); if ((unsigned int) f41 (0x12345678U, 3) != expected[41 - 1]) abort (); if ((unsigned int) f42 (0x12345678U, 3) != expected[42 - 1]) abort (); if ((unsigned int) f43 (0x12345678U, 3) != expected[43 - 1]) abort (); if ((unsigned int) f44 (0x12345678U, 3) != expected[44 - 1]) abort (); if ((unsigned int) f45 (0x12345678U, 3) != expected[45 - 1]) abort (); if ((unsigned int) f46 (0x12345678U, 3) != expected[46 - 1]) abort (); if ((unsigned int) f47 (0x12345678U, 3) != expected[47 - 1]) abort (); if ((unsigned int) f48 (0x12345678U, 3) != expected[48 - 1]) abort (); if ((unsigned int) f49 (0x12345678U, 3) != expected[49 - 1]) abort (); if ((unsigned int) f50 (0x12345678U, 3) != expected[50 - 1]) abort (); if ((unsigned int) f51 (0x12345678U, 3) != expected[51 - 1]) abort (); if ((unsigned int) f52 (0x12345678U, 3) != expected[52 - 1]) abort (); if ((unsigned int) f53 (0x12345678U, 3) != expected[53 - 1]) abort (); if ((unsigned int) f54 (0x12345678U, 3) != expected[54 - 1]) abort (); if ((unsigned int) f55 (0x12345678U, 3) != expected[55 - 1]) abort (); if ((unsigned int) f56 (0x12345678U, 3) != expected[56 - 1]) abort (); if ((unsigned int) f57 (0x12345678U, 3) != expected[57 - 1]) abort (); if ((unsigned int) f58 (0x12345678U, 3) != expected[58 - 1]) abort (); if ((unsigned int) f59 (0x12345678U, 3) != expected[59 - 1]) abort (); if ((unsigned int) f60 (0x12345678U, 3) != expected[60 - 1]) abort (); if ((unsigned int) f61 (0x12345678U, 3) != expected[61 - 1]) abort (); if ((unsigned int) f62 (0x12345678U, 3) != expected[62 - 1]) abort (); if ((unsigned int) f63 (0x12345678U, 3) != expected[63 - 1]) abort (); if ((unsigned int) f64 (0x12345678U, 3) != expected[64 - 1]) abort (); if ((unsigned int) f65 (0x12345678U, 3) != expected[65 - 1]) abort (); if ((unsigned int) f66 (0x12345678U, 3) != expected[66 - 1]) abort (); if ((unsigned int) f67 (0x12345678U, 3) != expected[67 - 1]) abort (); if ((unsigned int) f68 (0x12345678U, 3) != expected[68 - 1]) abort (); if ((unsigned int) f69 (0x12345678U, 3) != expected[69 - 1]) abort (); if ((unsigned int) f70 (0x12345678U, 3) != expected[70 - 1]) abort (); if ((unsigned int) f71 (0x12345678U, 3) != expected[71 - 1]) abort (); if ((unsigned int) f72 (0x12345678U, 3) != expected[72 - 1]) abort (); if ((unsigned int) f73 (0x12345678U, 3) != expected[73 - 1]) abort (); if ((unsigned int) f74 (0x12345678U, 3) != expected[74 - 1]) abort (); if ((unsigned int) f75 (0x12345678U, 3) != expected[75 - 1]) abort (); if ((unsigned int) f76 (0x12345678U, 3) != expected[76 - 1]) abort (); if ((unsigned int) f77 (0x12345678U, 3) != expected[77 - 1]) abort (); if ((unsigned int) f78 (0x12345678U, 3) != expected[78 - 1]) abort (); if ((unsigned int) f79 (0x12345678U, 3) != expected[79 - 1]) abort (); if ((unsigned int) f80 (0x12345678U, 3) != expected[80 - 1]) abort (); if ((unsigned int) f81 (0x12345678U, 3) != expected[81 - 1]) abort (); if ((unsigned int) f82 (0x12345678U, 3) != expected[82 - 1]) abort (); if ((unsigned int) f83 (0x12345678U, 3) != expected[83 - 1]) abort (); if ((unsigned int) f84 (0x12345678U, 3) != expected[84 - 1]) abort (); if ((unsigned int) f85 (0x12345678U, 3) != expected[85 - 1]) abort (); if ((unsigned int) f86 (0x12345678U, 3) != expected[86 - 1]) abort (); if ((unsigned int) f87 (0x12345678U, 3) != expected[87 - 1]) abort (); if ((unsigned int) f88 (0x12345678U, 3) != expected[88 - 1]) abort (); if ((unsigned int) f89 (0x12345678U, 3) != expected[89 - 1]) abort (); if ((unsigned int) f90 (0x12345678U, 3) != expected[90 - 1]) abort (); if ((unsigned int) f91 (0x12345678U, 3) != expected[91 - 1]) abort (); if ((unsigned int) f92 (0x12345678U, 3) != expected[92 - 1]) abort (); if ((unsigned int) f93 (0x12345678U, 3) != expected[93 - 1]) abort (); if ((unsigned int) f94 (0x12345678U, 3) != expected[94 - 1]) abort (); if ((unsigned int) f95 (0x12345678U, 3) != expected[95 - 1]) abort (); if ((unsigned int) f96 (0x12345678U, 3) != expected[96 - 1]) abort ();
  return 0;

}
