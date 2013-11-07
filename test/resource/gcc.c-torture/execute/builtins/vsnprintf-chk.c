



typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;

extern void abort (void);
typedef long unsigned int size_t;
extern size_t strlen(const char *);
extern void *memcpy (void *, const void *, size_t);
extern char *strcpy (char *, const char *);
extern int memcmp (const void *, const void *, size_t);
extern void *memset (void *, int, size_t);
extern int vsnprintf (char *, size_t, const char *, va_list);

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

int
__attribute__((noinline))
test1_sub (int i, ...)
{
  int ret = 0;
  va_list ap;
  __builtin_va_start(ap,i);
  switch (i)
    {
    case 0:
      __builtin___vsnprintf_chk (buffer, 4, 0, __builtin_object_size (buffer, 0), "foo", ap);
      break;
    case 1:
      ret = __builtin___vsnprintf_chk (buffer, 4, 0, __builtin_object_size (buffer, 0), "foo bar", ap);
      break;
    case 2:
      __builtin___vsnprintf_chk (buffer, 32, 0, __builtin_object_size (buffer, 0), "%s", ap);
      break;
    case 3:
      ret = __builtin___vsnprintf_chk (buffer, 21, 0, __builtin_object_size (buffer, 0), "%s", ap);
      break;
    case 4:
      ret = __builtin___vsnprintf_chk (buffer, 4, 0, __builtin_object_size (buffer, 0), "%d%d%d", ap);
      break;
    case 5:
      ret = __builtin___vsnprintf_chk (buffer, 32, 0, __builtin_object_size (buffer, 0), "%d%d%d", ap);
      break;
    case 6:
      ret = __builtin___vsnprintf_chk (buffer, strlen (ptr) + 1, 0, __builtin_object_size (buffer, 0), "%s", ap);
      break;
    case 7:
      __builtin___vsnprintf_chk (buffer, l1 + 31, 0, __builtin_object_size (buffer, 0), "%d - %c", ap);
      break;
    case 8:
      __builtin___vsnprintf_chk (s4, l1 + 6, 0, __builtin_object_size (s4, 0), "%d - %c", ap);
      break;
    }
  __builtin_va_end(ap);
  return ret;
}

void
__attribute__((noinline))
test1 (void)
{
  chk_calls = 0;


  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  test1_sub (0);
  if (memcmp (buffer, "foo", 4) || buffer[4] != 'A')
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  if (test1_sub (1) != 7)
    abort ();
  if (memcmp (buffer, "foo", 4) || buffer[4] != 'A')
    abort ();

  vsnprintf_disallowed = 0;

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  test1_sub (2, "bar");
  if (memcmp (buffer, "bar", 4) || buffer[4] != 'A')
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  if (test1_sub (3, "bar") != 3)
    abort ();
  if (memcmp (buffer, "bar", 4) || buffer[4] != 'A')
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  if (test1_sub (4, (int) l1, (int) l1 + 1, (int) l1 + 12) != 4)
    abort ();
  if (memcmp (buffer, "121", 4) || buffer[4] != 'A')
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  if (test1_sub (5, (int) l1, (int) l1 + 1, (int) l1 + 12) != 4)
    abort ();
  if (memcmp (buffer, "1213", 5) || buffer[5] != 'A')
    abort ();

  if (chk_calls)
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  test1_sub (6, ptr);
  if (memcmp (buffer, "barf", 5) || buffer[5] != 'A')
    abort ();

  __builtin___memset_chk (buffer, 'A', 32, __builtin_object_size (buffer, 0));
  test1_sub (7, (int) l1 + 27, *ptr);
  if (memcmp (buffer, "28 - b\0AAAAA", 12))
    abort ();

  if (chk_calls != 2)
    abort ();
  chk_calls = 0;

  __builtin___memset_chk (s4, 'A', 32, __builtin_object_size (s4, 0));
  test1_sub (8, (int) l1 - 17, ptr[1]);
  if (memcmp (s4, "-16 - \0AAA", 10))
    abort ();
  if (chk_calls)
    abort ();
}

void
__attribute__((noinline))
test2_sub (int i, ...)
{
  va_list ap;
  struct A { char buf1[10]; char buf2[10]; } a;
  char *r = l1 == 1 ? &a.buf1[5] : &a.buf2[4];
  char buf3[20];
  int j;

  __builtin_va_start(ap,i);


  switch (i)
    {
    case 0:
      __builtin___vsnprintf_chk (a.buf1 + 2, l1, 0, __builtin_object_size (a.buf1 + 2, 0), "%s", ap);
      break;
    case 1:
      __builtin___vsnprintf_chk (r, l1 + 4, 0, __builtin_object_size (r, 0), "%s%c", ap);
      break;
    case 2:
      r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
      __builtin___vsnprintf_chk (r, strlen (s2) - 2, 0, __builtin_object_size (r, 0), "%c %s", ap);
      break;
    case 3:
      r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
      __builtin___vsnprintf_chk (r + 2, l1, 0, __builtin_object_size (r + 2, 0), s3 + 3, ap);
      break;
    case 4:
    case 7:
      r = buf3;
      for (j = 0; j < 4; ++j)
 {
   if (j == l1 - 1)
     r = &a.buf1[1];
   else if (j == l1)
     r = &a.buf2[7];
   else if (j == l1 + 1)
     r = &buf3[5];
   else if (j == l1 + 2)
     r = &a.buf1[9];
 }
      if (i == 4)
 __builtin___vsnprintf_chk (r, l1, 0, __builtin_object_size (r, 0), s2 + 4, ap);
      else
 __builtin___vsnprintf_chk (r, 1, 0, __builtin_object_size (r, 0), "a", ap);
      break;
    case 5:
      r = l1 == 1 ? __builtin_alloca (4) : &a.buf2[7];
      __builtin___vsnprintf_chk (r, l1 + 3, 0, __builtin_object_size (r, 0), "%s", ap);
      break;
    case 6:
      __builtin___vsnprintf_chk (a.buf1 + 2, 4, 0, __builtin_object_size (a.buf1 + 2, 0), "", ap);
      break;
    case 8:
      __builtin___vsnprintf_chk (s4, 3, 0, __builtin_object_size (s4, 0), "%s %d", ap);
      break;
    }
  __builtin_va_end(ap);
}



void
__attribute__((noinline))
test2 (void)
{


  chk_calls = 0;
  test2_sub (0, s3 + 3);
  test2_sub (1, s3 + 3, s3[3]);
  test2_sub (2, s2[2], s2 + 4);
  test2_sub (3);
  test2_sub (4);
  test2_sub (5, s1 + 1);
  if (chk_calls != 6)
    abort ();




  chk_calls = 0;

  test2_sub (6);
  test2_sub (7);
  vsnprintf_disallowed = 0;

  test2_sub (8, s3, 0);
  if (chk_calls)
    abort ();
}

void
__attribute__((noinline))
test3_sub (int i, ...)
{
  va_list ap;
  struct A { char buf1[10]; char buf2[10]; } a;
  char buf3[20];

  __builtin_va_start(ap,i);


  switch (i)
    {
    case 0:
      __builtin___vsnprintf_chk (&a.buf2[9], l1 + 1, 0, __builtin_object_size (&a.buf2[9], 0), "%c%s", ap);
      break;
    case 1:
      __builtin___vsnprintf_chk (&a.buf2[7], l1 + 30, 0, __builtin_object_size (&a.buf2[7], 0), "%s%c", ap);
      break;
    case 2:
      __builtin___vsnprintf_chk (&a.buf2[7], l1 + 3, 0, __builtin_object_size (&a.buf2[7], 0), "%d", ap);
      break;
    case 3:
      __builtin___vsnprintf_chk (&buf3[17], l1 + 3, 0, __builtin_object_size (&buf3[17], 0), "%s", ap);
      break;
    case 4:
      __builtin___vsnprintf_chk (&buf3[19], 2, 0, __builtin_object_size (&buf3[19], 0), "a", ap);
      break;
    case 5:
      __builtin___vsnprintf_chk (&buf3[16], 5, 0, __builtin_object_size (&buf3[16], 0), "a", ap);
      break;
    }
  __builtin_va_end(ap);
}



void
__attribute__((noinline))
test3 (void)
{
  chk_fail_allowed = 1;

  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      test3_sub (0, s2[3], s2 + 4);
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      test3_sub (1, s3 + strlen (s3) - 2, *s3);
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      test3_sub (2, (int) l1 + 9999);
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      test3_sub (3, "abc");
      abort ();
    }

  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      test3_sub (4);
      abort ();
    }
  if (__builtin_setjmp (chk_fail_buf) == 0)
    {
      test3_sub (5);
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
