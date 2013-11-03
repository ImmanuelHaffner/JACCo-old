



int failures;
int
main ()
{
  do { typedef _Decimal32 type; typedef type **typepp; typedef __typeof__((3 + 2.1df)) ctype; typedef ctype **ctypepp; typepp x = 0; ctypepp y = 0; x = y; y = x; } while (0);
  do { typedef _Decimal32 type; typedef type **typepp; typedef __typeof__((1.3df + 2)) ctype; typedef ctype **ctypepp; typepp x = 0; ctypepp y = 0; x = y; y = x; } while (0);
  do { typedef _Decimal64 type; typedef type **typepp; typedef __typeof__((56U - 55.0dd)) ctype; typedef ctype **ctypepp; typepp x = 0; ctypepp y = 0; x = y; y = x; } while (0);
  do { typedef _Decimal128 type; typedef type **typepp; typedef __typeof__((5 * .2DL)) ctype; typedef ctype **ctypepp; typepp x = 0; ctypepp y = 0; x = y; y = x; } while (0);
  do { typedef _Decimal128 type; typedef type **typepp; typedef __typeof__((.88dl / 2L)) ctype; typedef ctype **ctypepp; typepp x = 0; ctypepp y = 0; x = y; y = x; } while (0);
  do { typedef _Decimal64 type; typedef type **typepp; typedef __typeof__((.114df - 1.6dd)) ctype; typedef ctype **ctypepp; typepp x = 0; ctypepp y = 0; x = y; y = x; } while (0);
  do { typedef _Decimal32 type; typedef type **typepp; typedef __typeof__((3L - 1 + .55df)) ctype; typedef ctype **ctypepp; typepp x = 0; ctypepp y = 0; x = y; y = x; } while (0);

  return 0;
}
