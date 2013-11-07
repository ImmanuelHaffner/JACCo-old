



extern void abort (void);
typedef long unsigned int size_t;
extern size_t strlen(const char *);
extern void *memcpy (void *, const void *, size_t);
extern char *strcpy (char *, const char *);
extern int memcmp (const void *, const void *, size_t);
extern void *memset (void *, int, size_t);
extern int sprintf (char *, const char *, ...);
extern int snprintf (char *, size_t, const char *, ...);

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
static char buffer[32];
char * volatile ptr = "barf";

void
__attribute__((noinline))
test1 (void)
{
  chk_calls = 0;


  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  __builtin___snprintf_chk (buffer, 4, 0, __builtin_object_size (buffer, 0), "foo");
  if (memcmp (buffer, "foo", 4) || buffer[4] != 'A')
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  if (__builtin___snprintf_chk (buffer, 4, 0, __builtin_object_size (buffer, 0), "foo bar") != 7)
    abort ();
  if (memcmp (buffer, "foo", 4) || buffer[4] != 'A')
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  __builtin___snprintf_chk (buffer, 32, 0, __builtin_object_size (buffer, 0), "%s", "bar");
  if (memcmp (buffer, "bar", 4) || buffer[4] != 'A')
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  if (__builtin___snprintf_chk (buffer, 21, 0, __builtin_object_size (buffer, 0), "%s", "bar") != 3)
    abort ();
  if (memcmp (buffer, "bar", 4) || buffer[4] != 'A')
    abort ();

  snprintf_disallowed = 0;

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  if (__builtin___snprintf_chk (buffer, 4, 0, __builtin_object_size (buffer, 0), "%d%d%d", (int) l1, (int) l1 + 1, (int) l1 + 12)
      != 4)
    abort ();
  if (memcmp (buffer, "121", 4) || buffer[4] != 'A')
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  if (__builtin___snprintf_chk (buffer, 32, 0, __builtin_object_size (buffer, 0), "%d%d%d", (int) l1, (int) l1 + 1, (int) l1 + 12)
      != 4)
    abort ();
  if (memcmp (buffer, "1213", 5) || buffer[5] != 'A')
    abort ();

  if (chk_calls)
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  __builtin___snprintf_chk (buffer, strlen (ptr) + 1, 0, __builtin_object_size (buffer, 0), "%s", ptr);
  if (memcmp (buffer, "barf", 5) || buffer[5] != 'A')
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  __builtin___snprintf_chk (buffer, l1 + 31, 0, __builtin_object_size (buffer, 0), "%d - %c", (int) l1 + 27, *ptr);
  if (memcmp (buffer, "28 - b\0AAAAA", 12))
    abort ();

  if (chk_calls != 2)
    abort ();
  chk_calls = 0;

  __builtin___memset_chk (s4, 'A', 32, __builtin_object_size (s4, 0));
  __builtin___snprintf_chk (s4, l1 + 6, 0, __builtin_object_size (s4, 0), "%d - %c", (int) l1 - 17, ptr[1]);
  if (memcmp (s4, "-16 - \0AAA", 10))
    abort ();
  if (chk_calls)
    abort ();
}



void
__attribute__((noinline))
test2 (void)
{
  struct A { char buf1[10]; char buf2[10]; } a;
  char *r = l1 == 1 ? &a.buf1[5] : &a.buf2[4];
  char buf3[20];
  int i;



  chk_calls = 0;
  __builtin___snprintf_chk (a.buf1 + 2, l1, 0, __builtin_object_size (a.buf1 + 2, 0), "%s", s3 + 3);
  __builtin___snprintf_chk (r, l1 + 4, 0, __builtin_object_size (r, 0), "%s%c", s3 + 3, s3[3]);
  r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
  __builtin___snprintf_chk (r, strlen (s2) - 2, 0, __builtin_object_size (r, 0), "%c %s", s2[2], s2 + 4);
  __builtin___snprintf_chk (r + 2, l1, 0, __builtin_object_size (r + 2, 0), s3 + 3);
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
  __builtin___snprintf_chk (r, l1, 0, __builtin_object_size (r, 0), s2 + 4);
  if (chk_calls != 5)
    abort ();




  chk_calls = 0;

  __builtin___snprintf_chk (a.buf1 + 2, 4, 0, __builtin_object_size (a.buf1 + 2, 0), "");
  __builtin___snprintf_chk (r, 1, 0, __builtin_object_size (r, 0), "a");
  r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
  __builtin___snprintf_chk (r, 3, 0, __builtin_object_size (r, 0), "%s", s1 + 1);
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
  __builtin___snprintf_chk (r, 1, 0, __builtin_object_size (r, 0), "%s", "");
  __builtin___snprintf_chk (r, 0, 0, __builtin_object_size (r, 0), "%s", "");
  snprintf_disallowed = 0;

  __builtin___snprintf_chk (s4, l1 + 31, 0, __builtin_object_size (s4, 0), "%s %d", s3, 0);
  if (chk_calls)
    abort ();
}



void
__attribute__((noinline))
test3 (void)
{
  struct A { char buf1[10]; char buf2[10]; } a;
  char buf3[20];

  chk_fail_allowed = 1;

  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      __builtin___snprintf_chk (&a.buf2[9], l1 + 1, 0, __builtin_object_size (&a.buf2[9], 0), "%c%s", s2[3], s2 + 4);
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      __builtin___snprintf_chk (&a.buf2[7], l1 + 30, 0, __builtin_object_size (&a.buf2[7], 0), "%s%c", s3 + strlen (s3) - 2, *s3);
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      __builtin___snprintf_chk (&a.buf2[7], l1 + 3, 0, __builtin_object_size (&a.buf2[7], 0), "%d", (int) l1 + 9999);
      abort ();
    }

  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      __builtin___snprintf_chk (&buf3[19], 2, 0, __builtin_object_size (&buf3[19], 0), "a");
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      __builtin___snprintf_chk (&buf3[17], 4, 0, __builtin_object_size (&buf3[17], 0), "a");
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      __builtin___snprintf_chk (&buf3[17], 4, 0, __builtin_object_size (&buf3[17], 0), "%s", "abc");
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
  test2 ();
  test3 ();
}
