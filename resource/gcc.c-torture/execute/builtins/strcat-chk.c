



extern void abort (void);
typedef long unsigned int size_t;
extern size_t strlen(const char *);
extern void *memcpy (void *, const void *, size_t);
extern char *strcat (char *, const char *);
extern int memcmp (const void *, const void *, size_t);
extern char *strcpy (char *, const char *);
extern int strcmp (const char *, const char *);
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
char *s2 = "defg";
char *s3 = "FGH";
char *s4;
size_t l1 = 1;
char *s5;

void
__attribute__((noinline))
test1 (void)
{
  const char *const x1 = "hello world";
  const char *const x2 = "";
  char dst[64], *d2;

  chk_calls = 0;
  strcat_disallowed = 1;

  do { __builtin___memset_chk (dst, 'X', sizeof (dst), __builtin_object_size (dst, 0)); __builtin___strcpy_chk (dst, (x1), __builtin_object_size (dst, 0)); } while (0);
  if (__builtin___strcat_chk (dst, "", __builtin_object_size (dst, 0)) != dst || strcmp (dst, x1))
    abort ();
  do { __builtin___memset_chk (dst, 'X', sizeof (dst), __builtin_object_size (dst, 0)); __builtin___strcpy_chk (dst, (x1), __builtin_object_size (dst, 0)); } while (0);
  if (__builtin___strcat_chk (dst, x2, __builtin_object_size (dst, 0)) != dst || strcmp (dst, x1))
    abort ();
  do { __builtin___memset_chk (dst, 'X', sizeof (dst), __builtin_object_size (dst, 0)); __builtin___strcpy_chk (dst, (x1), __builtin_object_size (dst, 0)); } while (0); d2 = dst;
  if (__builtin___strcat_chk (++d2, x2, __builtin_object_size (++d2, 0)) != dst+1 || d2 != dst+1 || strcmp (dst, x1))
    abort ();
  do { __builtin___memset_chk (dst, 'X', sizeof (dst), __builtin_object_size (dst, 0)); __builtin___strcpy_chk (dst, (x1), __builtin_object_size (dst, 0)); } while (0); d2 = dst;
  if (__builtin___strcat_chk (++d2+5, x2, __builtin_object_size (++d2+5, 0)) != dst+6 || d2 != dst+1 || strcmp (dst, x1))
    abort ();
  do { __builtin___memset_chk (dst, 'X', sizeof (dst), __builtin_object_size (dst, 0)); __builtin___strcpy_chk (dst, (x1), __builtin_object_size (dst, 0)); } while (0); d2 = dst;
  if (__builtin___strcat_chk (++d2+5, x1+11, __builtin_object_size (++d2+5, 0)) != dst+6 || d2 != dst+1 || strcmp (dst, x1))
    abort ();
  if (chk_calls)
    abort ();
  strcat_disallowed = 0;

  do { __builtin___memset_chk (dst, 'X', sizeof (dst), __builtin_object_size (dst, 0)); __builtin___strcpy_chk (dst, (x1), __builtin_object_size (dst, 0)); } while (0);
  if (__builtin___strcat_chk (dst, " 1111", __builtin_object_size (dst, 0)) != dst
      || memcmp (dst, "hello world 1111\0XXX", 20))
    abort ();

  do { __builtin___memset_chk (dst, 'X', sizeof (dst), __builtin_object_size (dst, 0)); __builtin___strcpy_chk (dst, (x1), __builtin_object_size (dst, 0)); } while (0);
  if (__builtin___strcat_chk (dst+5, " 2222", __builtin_object_size (dst+5, 0)) != dst+5
      || memcmp (dst, "hello world 2222\0XXX", 20))
    abort ();

  do { __builtin___memset_chk (dst, 'X', sizeof (dst), __builtin_object_size (dst, 0)); __builtin___strcpy_chk (dst, (x1), __builtin_object_size (dst, 0)); } while (0); d2 = dst;
  if (__builtin___strcat_chk (++d2+5, " 3333", __builtin_object_size (++d2+5, 0)) != dst+6 || d2 != dst+1
      || memcmp (dst, "hello world 3333\0XXX", 20))
    abort ();

  do { __builtin___memset_chk (dst, 'X', sizeof (dst), __builtin_object_size (dst, 0)); __builtin___strcpy_chk (dst, (x1), __builtin_object_size (dst, 0)); } while (0);
  __builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), "test", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), 0)), ".", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), "test", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), "a ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), "is ", __builtin_object_size (__builtin___strcat_chk (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), "", __builtin_object_size (__builtin___strcat_chk (dst, ": this ", __builtin_object_size (dst, 0)), 0)), 0)), 0)), 0)), 0))
                                  ;
  if (memcmp (dst, "hello world: this is a test.\0X", 30))
    abort ();

  chk_calls = 0;
  strcat_disallowed = 1;


  do { __builtin___memset_chk (dst, 'X', sizeof (dst), __builtin_object_size (dst, 0)); __builtin___strcpy_chk (dst, (x1), __builtin_object_size (dst, 0)); } while (0);
  if (__builtin___strcat_chk (dst, "", __builtin_object_size (dst, 0)) != dst || strcmp (dst, x1))
    abort ();
  if (chk_calls)
    abort ();
  strcat_disallowed = 0;
}




void
__attribute__((noinline))
test2 (void)
{
  struct A { char buf1[10]; char buf2[10]; } a;
  char *r = l1 == 1 ? &a.buf1[5] : &a.buf2[4];
  char buf3[20];
  int i;



  __builtin___memset_chk (&a, '\0', sizeof (a), __builtin_object_size (&a, 0));
  s5 = (char *) &a;
  __asm __volatile ("" : : "r" (s5) : "memory");
  chk_calls = 0;
  __builtin___strcat_chk (a.buf1 + 2, s3 + 3, __builtin_object_size (a.buf1 + 2, 0));
  __builtin___strcat_chk (r, s3 + 2, __builtin_object_size (r, 0));
  r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
  __builtin___memset_chk (r, '\0', 3, __builtin_object_size (r, 0));
  __asm __volatile ("" : : "r" (r) : "memory");
  __builtin___strcat_chk (r, s2 + 2, __builtin_object_size (r, 0));
  __builtin___strcat_chk (r + 2, s3 + 3, __builtin_object_size (r + 2, 0));
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
  __builtin___strcat_chk (r, s2 + 4, __builtin_object_size (r, 0));
  if (chk_calls != 5)
    abort ();




  __builtin___memset_chk (&a, '\0', sizeof (a), __builtin_object_size (&a, 0));
  chk_calls = 0;
  s5 = (char *) &a;
  __asm __volatile ("" : : "r" (s5) : "memory");
  __builtin___strcat_chk (a.buf1 + 2, "a", __builtin_object_size (a.buf1 + 2, 0));
  __builtin___strcat_chk (r, "", __builtin_object_size (r, 0));
  r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
  __builtin___memset_chk (r, '\0', 3, __builtin_object_size (r, 0));
  __asm __volatile ("" : : "r" (r) : "memory");
  __builtin___strcat_chk (r, s1 + 1, __builtin_object_size (r, 0));
  if (chk_calls != 2)
    abort ();
  chk_calls = 0;

  __builtin___strcat_chk (s4, s3, __builtin_object_size (s4, 0));
  if (chk_calls)
    abort ();
  chk_calls = 0;
}



void
__attribute__((noinline))
test3 (void)
{
  struct A { char buf1[10]; char buf2[10]; } a;
  char buf3[20];

  __builtin___memset_chk (&a, '\0', sizeof (a), __builtin_object_size (&a, 0));
  __builtin___memset_chk (buf3, '\0', sizeof (buf3), __builtin_object_size (buf3, 0));
  s5 = (char *) &a;
  __asm __volatile ("" : : "r" (s5) : "memory");
  s5 = buf3;
  __asm __volatile ("" : : "r" (s5) : "memory");
  chk_fail_allowed = 1;

  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      __builtin___strcat_chk (&a.buf2[9], s2 + 3, __builtin_object_size (&a.buf2[9], 0));
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      __builtin___strcat_chk (&a.buf2[7], s3 + strlen (s3) - 3, __builtin_object_size (&a.buf2[7], 0));
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      __builtin___strcat_chk (&buf3[19], "a", __builtin_object_size (&buf3[19], 0));
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
  s4 = p;
  test1 ();
  __builtin___memset_chk (p, '\0', sizeof (p), __builtin_object_size (p, 0));
  test2 ();
  test3 ();
}
