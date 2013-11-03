



extern void abort (void);
typedef long unsigned int size_t;
extern size_t strlen(const char *);
extern void *memcpy (void *, const void *, size_t);
extern char *stpncpy (char *, const char *, size_t);
extern int memcmp (const void *, const void *, size_t);
extern int strcmp (const char *, const char *);
extern int strncmp (const char *, const char *, size_t);
extern void *memset (void *, int, size_t);

extern void *chk_fail_buf[];
extern volatile int chk_fail_allowed, chk_calls;
extern volatile int memcpy_disallowed, mempcpy_disallowed, memmove_disallowed;
extern volatile int memset_disallowed, strcpy_disallowed, stpcpy_disallowed;
extern volatile int strncpy_disallowed, stpncpy_disallowed, strcat_disallowed;
extern volatile int strncat_disallowed, sprintf_disallowed, vsprintf_disallowed;
extern volatile int snprintf_disallowed, vsnprintf_disallowed;

const char s1[] = "123";
char p[32] = "";
char * volatile s2 = "defg";
char * volatile s3 = "FGH";
char *s4;
volatile size_t l1 = 1;
int i;

void
__attribute__((noinline))
test1 (void)
{
  const char *const src = "hello world";
  const char *src2;
  char dst[64], *dst2;

  chk_calls = 0;

  __builtin___memset_chk (dst, 0, sizeof (dst), __builtin_object_size (dst, 0));
  if (__builtin___stpncpy_chk (dst, src, 4, __builtin_object_size (dst, 0)) != dst+4 || strncmp (dst, src, 4))
    abort();

  __builtin___memset_chk (dst, 0, sizeof (dst), __builtin_object_size (dst, 0));
  if (__builtin___stpncpy_chk (dst+16, src, 4, __builtin_object_size (dst+16, 0)) != dst+20 || strncmp (dst+16, src, 4))
    abort();

  __builtin___memset_chk (dst, 0, sizeof (dst), __builtin_object_size (dst, 0));
  if (__builtin___stpncpy_chk (dst+32, src+5, 4, __builtin_object_size (dst+32, 0)) != dst+36 || strncmp (dst+32, src+5, 4))
    abort();

  __builtin___memset_chk (dst, 0, sizeof (dst), __builtin_object_size (dst, 0));
  dst2 = dst;
  if (__builtin___stpncpy_chk (++dst2, src+5, 4, __builtin_object_size (++dst2, 0)) != dst+5 || strncmp (dst2, src+5, 4)
      || dst2 != dst+1)
    abort();

  __builtin___memset_chk (dst, 0, sizeof (dst), __builtin_object_size (dst, 0));
  if (__builtin___stpncpy_chk (dst, src, 0, __builtin_object_size (dst, 0)) != dst || strcmp (dst, ""))
    abort();

  __builtin___memset_chk (dst, 0, sizeof (dst), __builtin_object_size (dst, 0));
  dst2 = dst; src2 = src;
  if (__builtin___stpncpy_chk (++dst2, ++src2, 0, __builtin_object_size (++dst2, 0)) != dst+1 || strcmp (dst2, "")
      || dst2 != dst+1 || src2 != src+1)
    abort();

  __builtin___memset_chk (dst, 0, sizeof (dst), __builtin_object_size (dst, 0));
  dst2 = dst; src2 = src;
  if (__builtin___stpncpy_chk (++dst2+5, ++src2+5, 0, __builtin_object_size (++dst2+5, 0)) != dst+6 || strcmp (dst2+5, "")
      || dst2 != dst+1 || src2 != src+1)
    abort();

  __builtin___memset_chk (dst, 0, sizeof (dst), __builtin_object_size (dst, 0));
  if (__builtin___stpncpy_chk (dst, src, 12, __builtin_object_size (dst, 0)) != dst+11 || strcmp (dst, src))
    abort();



  __builtin___memset_chk (dst, 0, sizeof (dst), __builtin_object_size (dst, 0));
  if (__builtin_stpncpy (dst, src, 4) != dst+4 || strncmp (dst, src, 4))
    abort();

  __builtin___memset_chk (dst, 0, sizeof (dst), __builtin_object_size (dst, 0));
  if (__builtin___stpncpy_chk (dst, i++ ? "xfoo" + 1 : "bar", 4, __builtin_object_size (dst, 0)) != dst+3
      || strcmp (dst, "bar")
      || i != 1)
    abort ();



  stpncpy_disallowed = 1;
  __builtin___stpncpy_chk (dst + 1, src, 4, __builtin_object_size (dst + 1, 0));
  stpncpy_disallowed = 0;
  if (strncmp (dst + 1, src, 4))
    abort ();

  if (chk_calls)
    abort ();
}

void
__attribute__((noinline))
test2 (void)
{
  chk_calls = 0;



  size_t cpy_length = l1 < 4 ? l1 + 1 : 4;
  if (__builtin___stpncpy_chk (s4, "abcd", l1 + 1, __builtin_object_size (s4, 0)) != s4 + cpy_length || strncmp (s4, "abcd", cpy_length))
    abort ();

  if (chk_calls)
    abort ();
}



void
__attribute__((noinline))
test3 (void)
{
  struct A { char buf1[10]; char buf2[10]; } a;
  char *r = l1 == 1 ? &a.buf1[5] : &a.buf2[4];
  char buf3[20];
  int i;
  const char *l;
  size_t l2;





  chk_calls = 0;
  if (!__builtin___stpncpy_chk (a.buf1 + 2, s3 + 3, l1, __builtin_object_size (a.buf1 + 2, 0)))
    abort();
  if (!__builtin___stpncpy_chk (r, s3 + 2, l1 + 2, __builtin_object_size (r, 0)))
    abort();
  r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
  if (!__builtin___stpncpy_chk (r, s2 + 2, l1 + 2, __builtin_object_size (r, 0)))
    abort();
  if (!__builtin___stpncpy_chk (r + 2, s3 + 3, l1, __builtin_object_size (r + 2, 0)))
    abort();
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
  if (!__builtin___stpncpy_chk (r, s2 + 4, l1, __builtin_object_size (r, 0)))
    abort();
  if (chk_calls != 5)
    abort ();




  chk_calls = 0;
  if (!__builtin___stpncpy_chk (a.buf1 + 2, "", 3, __builtin_object_size (a.buf1 + 2, 0)))
    abort ();
  if (!__builtin___stpncpy_chk (a.buf1 + 2, "", 0, __builtin_object_size (a.buf1 + 2, 0)))
    abort ();
  if (!__builtin___stpncpy_chk (r, "a", 1, __builtin_object_size (r, 0)))
    abort ();
  if (!__builtin___stpncpy_chk (r, "a", 3, __builtin_object_size (r, 0)))
    abort ();
  r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
  if (!__builtin___stpncpy_chk (r, s1 + 1, 3, __builtin_object_size (r, 0)))
    abort ();
  if (!__builtin___stpncpy_chk (r, s1 + 1, 2, __builtin_object_size (r, 0)))
    abort ();
  r = buf3;
  l = "abc";
  l2 = 4;
  for (i = 0; i < 4; ++i)
    {
      if (i == l1 - 1)
 r = &a.buf1[1], l = "e", l2 = 2;
      else if (i == l1)
 r = &a.buf2[7], l = "gh", l2 = 3;
      else if (i == l1 + 1)
 r = &buf3[5], l = "jkl", l2 = 4;
      else if (i == l1 + 2)
 r = &a.buf1[9], l = "", l2 = 1;
    }
  if (!__builtin___stpncpy_chk (r, "", 1, __builtin_object_size (r, 0)))
    abort ();



  if (!__builtin___stpncpy_chk (&buf3[16], l, l2, __builtin_object_size (&buf3[16], 0)))
    abort ();
  if (!__builtin___stpncpy_chk (&buf3[15], "abc", l2, __builtin_object_size (&buf3[15], 0)))
    abort ();
  if (!__builtin___stpncpy_chk (&buf3[10], "fghij", l2, __builtin_object_size (&buf3[10], 0)))
    abort ();
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
      if (__builtin___stpncpy_chk (&a.buf2[9], s2 + 4, l1 + 1, __builtin_object_size (&a.buf2[9], 0)))


        i++;
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      if (__builtin___stpncpy_chk (&a.buf2[7], s3, l1 + 4, __builtin_object_size (&a.buf2[7], 0)))
        i++;
      abort ();
    }

  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      if (__builtin___stpncpy_chk (&buf3[19], "abc", 2, __builtin_object_size (&buf3[19], 0)))
        i++;
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      if (__builtin___stpncpy_chk (&buf3[18], "", 3, __builtin_object_size (&buf3[18], 0)))
        i++;
      abort ();
    }
  chk_fail_allowed = 0;
}

void
main_test (void)
{


  return;

  __asm ("" : "=r" (s2) : "0" (s2));
  __asm ("" : "=r" (s3) : "0" (s3));
  __asm ("" : "=r" (l1) : "0" (l1));
  test1 ();

  s4 = p;
  test2 ();
  test3 ();
  test4 ();
}
