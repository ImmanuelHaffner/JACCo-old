



extern void abort (void);
typedef long unsigned int size_t;
extern size_t strlen(const char *);
extern void *memcpy (void *, const void *, size_t);
extern void *mempcpy (void *, const void *, size_t);
extern int memcmp (const void *, const void *, size_t);

extern void *chk_fail_buf[];
extern volatile int chk_fail_allowed, chk_calls;
extern volatile int memcpy_disallowed, mempcpy_disallowed, memmove_disallowed;
extern volatile int memset_disallowed, strcpy_disallowed, stpcpy_disallowed;
extern volatile int strncpy_disallowed, stpncpy_disallowed, strcat_disallowed;
extern volatile int strncat_disallowed, sprintf_disallowed, vsprintf_disallowed;
extern volatile int snprintf_disallowed, vsnprintf_disallowed;

const char s1[] = "123";
char p[32] = "";
volatile char *s2 = "defg";
volatile char *s3 = "FGH";
volatile size_t l1 = 1;

void
__attribute__((noinline))
test1 (void)
{
  int i;





  mempcpy_disallowed = 1;




  chk_calls = 0;

  if (__builtin___mempcpy_chk (p, "ABCDE", 6, __builtin_object_size (p, 0)) != p + 6 || memcmp (p, "ABCDE", 6))
    abort ();
  if (__builtin___mempcpy_chk (p + 16, "VWX" + 1, 2, __builtin_object_size (p + 16, 0)) != p + 16 + 2
      || memcmp (p + 16, "WX\0\0", 5))
    abort ();
  if (__builtin___mempcpy_chk (p + 1, "", 1, __builtin_object_size (p + 1, 0)) != p + 1 + 1 || memcmp (p, "A\0CDE", 6))
    abort ();
  if (__builtin___mempcpy_chk (p + 3, "FGHI", 4, __builtin_object_size (p + 3, 0)) != p + 3 + 4 || memcmp (p, "A\0CFGHI", 8))
    abort ();

  i = 8;
  __builtin___memcpy_chk (p + 20, "qrstu", 6, __builtin_object_size (p + 20, 0));
  __builtin___memcpy_chk (p + 25, "QRSTU", 6, __builtin_object_size (p + 25, 0));
  if (__builtin___mempcpy_chk (p + 25 + 1, s1, 3, __builtin_object_size (p + 25 + 1, 0)) != (p + 25 + 1 + 3)
      || memcmp (p + 25, "Q123U", 6))
    abort ();

  if (__builtin___mempcpy_chk (__builtin___mempcpy_chk (p, "abcdEFG", 4, __builtin_object_size (p, 0)), "efg", 4, __builtin_object_size (__builtin___mempcpy_chk (p, "abcdEFG", 4, __builtin_object_size (p, 0)), 0)) != p + 8
      || memcmp (p, "abcdefg", 8))
    abort();



  if (__builtin___mempcpy_chk (p, "ABCDE", 6, __builtin_object_size (p, 0)) != p + 6 || memcmp (p, "ABCDE", 6))
    abort ();



  mempcpy_disallowed = 1;
  __builtin___mempcpy_chk (p + 5, s3, 1, __builtin_object_size (p + 5, 0));
  if (memcmp (p, "ABCDEFg", 8))
    abort ();

  if (chk_calls)
    abort ();
  chk_calls = 0;

  __builtin___mempcpy_chk (p + 6, s1 + 1, l1, __builtin_object_size (p + 6, 0));
  if (memcmp (p, "ABCDEF2", 8))
    abort ();




  if (chk_calls != 1)
    abort ();

  mempcpy_disallowed = 0;
}

long buf1[64];
char *buf2 = (char *) (buf1 + 32);
long buf5[20];
char buf7[20];

void
__attribute__((noinline))
test2_sub (long *buf3, char *buf4, char *buf6, int n)
{
  int i = 0;





  chk_calls = 0;


  if (__builtin___mempcpy_chk (buf1, "ABCDEFGHI", 9, __builtin_object_size (buf1, 0)) != (char *) buf1 + 9
      || memcmp (buf1, "ABCDEFGHI\0", 11))
    abort ();

  if (__builtin___mempcpy_chk (buf1, "abcdefghijklmnopq", 17, __builtin_object_size (buf1, 0)) != (char *) buf1 + 17
      || memcmp (buf1, "abcdefghijklmnopq\0", 19))
    abort ();

  if (__builtin___mempcpy_chk (buf3, "ABCDEF", 6, __builtin_object_size (buf3, 0)) != (char *) buf1 + 6
      || memcmp (buf1, "ABCDEFghijklmnopq\0", 19))
    abort ();

  if (__builtin___mempcpy_chk (buf3, "a", 1, __builtin_object_size (buf3, 0)) != (char *) buf1 + 1
      || memcmp (buf1, "aBCDEFghijklmnopq\0", 19))
    abort ();

  if (__builtin___mempcpy_chk ((char *) buf3 + 2, "bcd" + ++i, 2, __builtin_object_size ((char *) buf3 + 2, 0)) != (char *) buf1 + 4
      || memcmp (buf1, "aBcdEFghijklmnopq\0", 19)
      || i != 1)
    abort ();


  if (__builtin___mempcpy_chk ((char *) buf3 + 4, buf5, 6, __builtin_object_size ((char *) buf3 + 4, 0)) != (char *) buf1 + 10
      || memcmp (buf1, "aBcdRSTUVWklmnopq\0", 19))
    abort ();

  if (__builtin___mempcpy_chk ((char *) buf1 + ++i + 8, (char *) buf5 + 1, 1, __builtin_object_size ((char *) buf1 + ++i + 8, 0))
      != (char *) buf1 + 11
      || memcmp (buf1, "aBcdRSTUVWSlmnopq\0", 19)
      || i != 2)
    abort ();

  if (__builtin___mempcpy_chk ((char *) buf3 + 14, buf6, 2, __builtin_object_size ((char *) buf3 + 14, 0)) != (char *) buf1 + 16
      || memcmp (buf1, "aBcdRSTUVWSlmnrsq\0", 19))
    abort ();

  if (__builtin___mempcpy_chk (buf3, buf5, 8, __builtin_object_size (buf3, 0)) != (char *) buf1 + 8
      || memcmp (buf1, "RSTUVWXYVWSlmnrsq\0", 19))
    abort ();

  if (__builtin___mempcpy_chk (buf3, buf5, 17, __builtin_object_size (buf3, 0)) != (char *) buf1 + 17
      || memcmp (buf1, "RSTUVWXYZ01234567\0", 19))
    abort ();

  __builtin___memcpy_chk (buf3, "aBcdEFghijklmnopq\0", 19, __builtin_object_size (buf3, 0));





  if (__builtin___mempcpy_chk ((char *) buf3 + 4, buf5, n + 6, __builtin_object_size ((char *) buf3 + 4, 0)) != (char *) buf1 + 10
      || memcmp (buf1, "aBcdRSTUVWklmnopq\0", 19))
    abort ();


  if (__builtin___mempcpy_chk ((char *) buf1 + ++i + 8, (char *) buf5 + 1,
          n + 1, __builtin_object_size ((char *) buf1 + ++i + 8, 0))
      != (char *) buf1 + 12
      || memcmp (buf1, "aBcdRSTUVWkSmnopq\0", 19)
      || i != 3)
    abort ();

  if (__builtin___mempcpy_chk ((char *) buf3 + 14, buf6, n + 2, __builtin_object_size ((char *) buf3 + 14, 0)) != (char *) buf1 + 16
      || memcmp (buf1, "aBcdRSTUVWkSmnrsq\0", 19))
    abort ();

  i = 1;


  if (__builtin___mempcpy_chk (buf2, "ABCDEFGHI", 9, __builtin_object_size (buf2, 0)) != buf2 + 9
      || memcmp (buf2, "ABCDEFGHI\0", 11))
    abort ();

  if (__builtin___mempcpy_chk (buf2, "abcdefghijklmnopq", 17, __builtin_object_size (buf2, 0)) != buf2 + 17
      || memcmp (buf2, "abcdefghijklmnopq\0", 19))
    abort ();

  if (__builtin___mempcpy_chk (buf4, "ABCDEF", 6, __builtin_object_size (buf4, 0)) != buf2 + 6
      || memcmp (buf2, "ABCDEFghijklmnopq\0", 19))
    abort ();

  if (__builtin___mempcpy_chk (buf4, "a", 1, __builtin_object_size (buf4, 0)) != buf2 + 1
      || memcmp (buf2, "aBCDEFghijklmnopq\0", 19))
    abort ();

  if (__builtin___mempcpy_chk (buf4 + 2, "bcd" + i++, 2, __builtin_object_size (buf4 + 2, 0)) != buf2 + 4
      || memcmp (buf2, "aBcdEFghijklmnopq\0", 19)
      || i != 2)
    abort ();


  if (__builtin___mempcpy_chk (buf4 + 4, buf7, 6, __builtin_object_size (buf4 + 4, 0)) != buf2 + 10
      || memcmp (buf2, "aBcdRSTUVWklmnopq\0", 19))
    abort ();


  if (__builtin___mempcpy_chk (buf2 + i++ + 8, buf7 + 1, 1,
          __builtin_object_size (buf2 + i++ + 8, 0))
      != buf2 + 11
      || memcmp (buf2, "aBcdRSTUVWSlmnopq\0", 19)
      || i != 3)
    abort ();

  if (__builtin___mempcpy_chk (buf4 + 14, buf6, 2, __builtin_object_size (buf4 + 14, 0)) != buf2 + 16
      || memcmp (buf2, "aBcdRSTUVWSlmnrsq\0", 19))
    abort ();

  __builtin___memcpy_chk (buf4, "aBcdEFghijklmnopq\0", 19, __builtin_object_size (buf4, 0));



  if (__builtin___mempcpy_chk (buf4 + 4, buf7, n + 6, __builtin_object_size (buf4 + 4, 0)) != buf2 + 10
      || memcmp (buf2, "aBcdRSTUVWklmnopq\0", 19))
    abort ();


  if (__builtin___mempcpy_chk (buf2 + i++ + 8, buf7 + 1,
          n + 1, __builtin_object_size (buf2 + i++ + 8, 0))
      != buf2 + 12
      || memcmp (buf2, "aBcdRSTUVWkSmnopq\0", 19)
      || i != 4)
    abort ();

  if (__builtin___mempcpy_chk (buf4 + 14, buf6, n + 2, __builtin_object_size (buf4 + 14, 0)) != buf2 + 16
      || memcmp (buf2, "aBcdRSTUVWkSmnrsq\0", 19))
    abort ();

  if (chk_calls)
    abort ();
}

void
__attribute__((noinline))
test2 (void)
{
  long *x;
  char *y;
  int z;
  __builtin___memcpy_chk (buf5, "RSTUVWXYZ0123456789", 20, __builtin_object_size (buf5, 0));
  __builtin___memcpy_chk (buf7, "RSTUVWXYZ0123456789", 20, __builtin_object_size (buf7, 0));
 __asm ("" : "=r" (x) : "0" (buf1));
 __asm ("" : "=r" (y) : "0" (buf2));
 __asm ("" : "=r" (z) : "0" (0));
  test2_sub (x, y, "rstuvwxyz", z);
}

volatile void *vx;



void
__attribute__((noinline))
test3 (void)
{
  struct A { char buf1[10]; char buf2[10]; } a;
  char *r = l1 == 1 ? &a.buf1[5] : &a.buf2[4];
  char buf3[20];
  int i;
  size_t l;



  chk_calls = 0;
  vx = __builtin___mempcpy_chk (a.buf1 + 2, s3, l1, __builtin_object_size (a.buf1 + 2, 0));
  vx = __builtin___mempcpy_chk (r, s3, l1 + 1, __builtin_object_size (r, 0));
  r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
  vx = __builtin___mempcpy_chk (r, s2, l1 + 2, __builtin_object_size (r, 0));
  vx = __builtin___mempcpy_chk (r + 2, s3, l1, __builtin_object_size (r + 2, 0));
  r = buf3;
  for (i = 0; i < 4; ++i)
    {
      if (i == l1 - 1)
 r = &a.buf1[1];
      else if (i == l1)
 r = &a.buf2[7];
      else if (i == l1 + 1)
 r = &buf3[5];
      else if (i == l1 + 2)
 r = &a.buf1[9];
    }
  vx = __builtin___mempcpy_chk (r, s2, l1, __builtin_object_size (r, 0));
  if (chk_calls != 5)
    abort ();




  chk_calls = 0;
  vx = __builtin___mempcpy_chk (a.buf1 + 2, s3, 1, __builtin_object_size (a.buf1 + 2, 0));
  vx = __builtin___mempcpy_chk (r, s3, 2, __builtin_object_size (r, 0));
  r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
  vx = __builtin___mempcpy_chk (r, s2, 3, __builtin_object_size (r, 0));
  r = buf3;
  l = 4;
  for (i = 0; i < 4; ++i)
    {
      if (i == l1 - 1)
 r = &a.buf1[1], l = 2;
      else if (i == l1)
 r = &a.buf2[7], l = 3;
      else if (i == l1 + 1)
 r = &buf3[5], l = 4;
      else if (i == l1 + 2)
 r = &a.buf1[9], l = 1;
    }
  vx = __builtin___mempcpy_chk (r, s2, 1, __builtin_object_size (r, 0));


  vx = __builtin___mempcpy_chk (&buf3[16], s2, l, __builtin_object_size (&buf3[16], 0));
  if (chk_calls)
    abort ();
  chk_calls = 0;
}



void
__attribute__((noinline))
test4 (void)
{
  struct A { char buf1[10]; char buf2[10]; } a;
  char buf3[20];

  chk_fail_allowed = 1;

  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      vx = __builtin___mempcpy_chk (&a.buf2[9], s2, l1 + 1, __builtin_object_size (&a.buf2[9], 0));
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      vx = __builtin___mempcpy_chk (&a.buf2[7], s3, strlen (s3) + 1, __builtin_object_size (&a.buf2[7], 0));
      abort ();
    }

  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      vx = __builtin___mempcpy_chk (&buf3[19], "ab", 2, __builtin_object_size (&buf3[19], 0));
      abort ();
    }
  chk_fail_allowed = 0;
}
static union {
  char buf[((sizeof (long long)) + (10 * sizeof (long long)) + (sizeof (long long)))];
  long long align_int;
  long double align_fp;
} u1, u2;

void
__attribute__((noinline))
test5 (void)
{
  int off1, off2, len, i;
  char *p, *q, c;

  for (off1 = 0; off1 < (sizeof (long long)); off1++)
    for (off2 = 0; off2 < (sizeof (long long)); off2++)
      for (len = 1; len < (10 * sizeof (long long)); len++)
 {
   for (i = 0, c = 'A'; i < ((sizeof (long long)) + (10 * sizeof (long long)) + (sizeof (long long))); i++, c++)
     {
       u1.buf[i] = 'a';
       if (c >= 'A' + 31)
  c = 'A';
       u2.buf[i] = c;
     }

   p = __builtin___mempcpy_chk (u1.buf + off1, u2.buf + off2, len, __builtin_object_size (u1.buf + off1, 0));
   if (p != u1.buf + off1 + len)
     abort ();

   q = u1.buf;
   for (i = 0; i < off1; i++, q++)
     if (*q != 'a')
       abort ();

   for (i = 0, c = 'A' + off2; i < len; i++, q++, c++)
     {
       if (c >= 'A' + 31)
  c = 'A';
       if (*q != c)
  abort ();
     }

   for (i = 0; i < (sizeof (long long)); i++, q++)
     if (*q != 'a')
       abort ();
 }
}



char srcb[80] __attribute__ ((aligned));
char dstb[80] __attribute__ ((aligned));

void
__attribute__((noinline))
check (char *test, char *match, int n)
{
  if (memcmp (test, match, n))
    abort ();
}
void
__attribute__((noinline))
test6 (void)
{
  int i;

  chk_calls = 0;

  for (i = 0; i < sizeof (srcb); ++i)
      srcb[i] = 'a' + i % 26;

  { __builtin___memset_chk (dstb, 0, 0, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 0, __builtin_object_size (dstb, 0)); check (dstb, srcb, 0); } { __builtin___memset_chk (dstb, 0, (0) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (0) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (0) + 1); } { __builtin___memset_chk (dstb, 0, (0) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (0) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (0) + 2); } { __builtin___memset_chk (dstb, 0, (0) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (0) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (0) + 3); };
  { __builtin___memset_chk (dstb, 0, 4, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 4, __builtin_object_size (dstb, 0)); check (dstb, srcb, 4); } { __builtin___memset_chk (dstb, 0, (4) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (4) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (4) + 1); } { __builtin___memset_chk (dstb, 0, (4) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (4) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (4) + 2); } { __builtin___memset_chk (dstb, 0, (4) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (4) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (4) + 3); };
  { __builtin___memset_chk (dstb, 0, 8, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 8, __builtin_object_size (dstb, 0)); check (dstb, srcb, 8); } { __builtin___memset_chk (dstb, 0, (8) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (8) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (8) + 1); } { __builtin___memset_chk (dstb, 0, (8) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (8) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (8) + 2); } { __builtin___memset_chk (dstb, 0, (8) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (8) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (8) + 3); };
  { __builtin___memset_chk (dstb, 0, 12, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 12, __builtin_object_size (dstb, 0)); check (dstb, srcb, 12); } { __builtin___memset_chk (dstb, 0, (12) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (12) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (12) + 1); } { __builtin___memset_chk (dstb, 0, (12) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (12) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (12) + 2); } { __builtin___memset_chk (dstb, 0, (12) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (12) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (12) + 3); };
  { __builtin___memset_chk (dstb, 0, 16, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 16, __builtin_object_size (dstb, 0)); check (dstb, srcb, 16); } { __builtin___memset_chk (dstb, 0, (16) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (16) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (16) + 1); } { __builtin___memset_chk (dstb, 0, (16) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (16) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (16) + 2); } { __builtin___memset_chk (dstb, 0, (16) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (16) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (16) + 3); };
  { __builtin___memset_chk (dstb, 0, 20, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 20, __builtin_object_size (dstb, 0)); check (dstb, srcb, 20); } { __builtin___memset_chk (dstb, 0, (20) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (20) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (20) + 1); } { __builtin___memset_chk (dstb, 0, (20) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (20) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (20) + 2); } { __builtin___memset_chk (dstb, 0, (20) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (20) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (20) + 3); };
  { __builtin___memset_chk (dstb, 0, 24, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 24, __builtin_object_size (dstb, 0)); check (dstb, srcb, 24); } { __builtin___memset_chk (dstb, 0, (24) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (24) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (24) + 1); } { __builtin___memset_chk (dstb, 0, (24) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (24) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (24) + 2); } { __builtin___memset_chk (dstb, 0, (24) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (24) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (24) + 3); };
  { __builtin___memset_chk (dstb, 0, 28, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 28, __builtin_object_size (dstb, 0)); check (dstb, srcb, 28); } { __builtin___memset_chk (dstb, 0, (28) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (28) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (28) + 1); } { __builtin___memset_chk (dstb, 0, (28) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (28) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (28) + 2); } { __builtin___memset_chk (dstb, 0, (28) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (28) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (28) + 3); };
  { __builtin___memset_chk (dstb, 0, 32, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 32, __builtin_object_size (dstb, 0)); check (dstb, srcb, 32); } { __builtin___memset_chk (dstb, 0, (32) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (32) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (32) + 1); } { __builtin___memset_chk (dstb, 0, (32) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (32) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (32) + 2); } { __builtin___memset_chk (dstb, 0, (32) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (32) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (32) + 3); };
  { __builtin___memset_chk (dstb, 0, 36, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 36, __builtin_object_size (dstb, 0)); check (dstb, srcb, 36); } { __builtin___memset_chk (dstb, 0, (36) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (36) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (36) + 1); } { __builtin___memset_chk (dstb, 0, (36) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (36) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (36) + 2); } { __builtin___memset_chk (dstb, 0, (36) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (36) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (36) + 3); };
  { __builtin___memset_chk (dstb, 0, 40, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 40, __builtin_object_size (dstb, 0)); check (dstb, srcb, 40); } { __builtin___memset_chk (dstb, 0, (40) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (40) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (40) + 1); } { __builtin___memset_chk (dstb, 0, (40) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (40) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (40) + 2); } { __builtin___memset_chk (dstb, 0, (40) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (40) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (40) + 3); };
  { __builtin___memset_chk (dstb, 0, 44, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 44, __builtin_object_size (dstb, 0)); check (dstb, srcb, 44); } { __builtin___memset_chk (dstb, 0, (44) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (44) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (44) + 1); } { __builtin___memset_chk (dstb, 0, (44) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (44) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (44) + 2); } { __builtin___memset_chk (dstb, 0, (44) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (44) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (44) + 3); };
  { __builtin___memset_chk (dstb, 0, 48, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 48, __builtin_object_size (dstb, 0)); check (dstb, srcb, 48); } { __builtin___memset_chk (dstb, 0, (48) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (48) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (48) + 1); } { __builtin___memset_chk (dstb, 0, (48) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (48) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (48) + 2); } { __builtin___memset_chk (dstb, 0, (48) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (48) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (48) + 3); };
  { __builtin___memset_chk (dstb, 0, 52, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 52, __builtin_object_size (dstb, 0)); check (dstb, srcb, 52); } { __builtin___memset_chk (dstb, 0, (52) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (52) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (52) + 1); } { __builtin___memset_chk (dstb, 0, (52) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (52) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (52) + 2); } { __builtin___memset_chk (dstb, 0, (52) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (52) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (52) + 3); };
  { __builtin___memset_chk (dstb, 0, 56, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 56, __builtin_object_size (dstb, 0)); check (dstb, srcb, 56); } { __builtin___memset_chk (dstb, 0, (56) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (56) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (56) + 1); } { __builtin___memset_chk (dstb, 0, (56) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (56) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (56) + 2); } { __builtin___memset_chk (dstb, 0, (56) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (56) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (56) + 3); };
  { __builtin___memset_chk (dstb, 0, 60, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 60, __builtin_object_size (dstb, 0)); check (dstb, srcb, 60); } { __builtin___memset_chk (dstb, 0, (60) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (60) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (60) + 1); } { __builtin___memset_chk (dstb, 0, (60) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (60) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (60) + 2); } { __builtin___memset_chk (dstb, 0, (60) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (60) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (60) + 3); };
  { __builtin___memset_chk (dstb, 0, 64, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 64, __builtin_object_size (dstb, 0)); check (dstb, srcb, 64); } { __builtin___memset_chk (dstb, 0, (64) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (64) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (64) + 1); } { __builtin___memset_chk (dstb, 0, (64) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (64) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (64) + 2); } { __builtin___memset_chk (dstb, 0, (64) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (64) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (64) + 3); };
  { __builtin___memset_chk (dstb, 0, 68, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 68, __builtin_object_size (dstb, 0)); check (dstb, srcb, 68); } { __builtin___memset_chk (dstb, 0, (68) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (68) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (68) + 1); } { __builtin___memset_chk (dstb, 0, (68) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (68) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (68) + 2); } { __builtin___memset_chk (dstb, 0, (68) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (68) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (68) + 3); };
  { __builtin___memset_chk (dstb, 0, 72, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 72, __builtin_object_size (dstb, 0)); check (dstb, srcb, 72); } { __builtin___memset_chk (dstb, 0, (72) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (72) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (72) + 1); } { __builtin___memset_chk (dstb, 0, (72) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (72) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (72) + 2); } { __builtin___memset_chk (dstb, 0, (72) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (72) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (72) + 3); };
  { __builtin___memset_chk (dstb, 0, 76, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, 76, __builtin_object_size (dstb, 0)); check (dstb, srcb, 76); } { __builtin___memset_chk (dstb, 0, (76) + 1, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (76) + 1, __builtin_object_size (dstb, 0)); check (dstb, srcb, (76) + 1); } { __builtin___memset_chk (dstb, 0, (76) + 2, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (76) + 2, __builtin_object_size (dstb, 0)); check (dstb, srcb, (76) + 2); } { __builtin___memset_chk (dstb, 0, (76) + 3, __builtin_object_size (dstb, 0)); vx = __builtin___mempcpy_chk (dstb, srcb, (76) + 3, __builtin_object_size (dstb, 0)); check (dstb, srcb, (76) + 3); };


  if (chk_calls)
    abort ();
}

void
main_test (void)
{


  return;

  __asm ("" : "=r" (l1) : "0" (l1));
  test1 ();
  test2 ();
  test3 ();
  test4 ();
  test5 ();
  test6 ();
}
