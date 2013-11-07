

extern void abort (void);
typedef long unsigned int size_t;
extern size_t strlen (const char *);
extern void *memcpy (void *, const void *, size_t);
extern void *mempcpy (void *, const void *, size_t);
extern void *memmove (void *, const void *, size_t);
extern int snprintf (char *, size_t, const char *, ...);
extern int memcmp (const void *, const void *, size_t);

extern void *chk_fail_buf[];
extern volatile int chk_fail_allowed, chk_calls;
extern volatile int memcpy_disallowed, mempcpy_disallowed, memmove_disallowed;
extern volatile int memset_disallowed, strcpy_disallowed, stpcpy_disallowed;
extern volatile int strncpy_disallowed, stpncpy_disallowed, strcat_disallowed;
extern volatile int strncat_disallowed, sprintf_disallowed, vsprintf_disallowed;
extern volatile int snprintf_disallowed, vsnprintf_disallowed;

static char data[8] = "ABCDEFG";

int l1;

void
__attribute__((noinline))
test1 (void)
{
  char buf[8];



  chk_calls = 0;

  __builtin___memset_chk (buf, 'I', sizeof (buf), __builtin_object_size (buf, 0));
  if (__builtin___memcpy_chk (buf, data, l1 ? sizeof (buf) : 4, __builtin_object_size (buf, 0)) != buf
      || memcmp (buf, "ABCDIIII", 8))
    abort ();

  __builtin___memset_chk (buf, 'J', sizeof (buf), __builtin_object_size (buf, 0));
  if (__builtin___mempcpy_chk (buf, data, l1 ? sizeof (buf) : 4, __builtin_object_size (buf, 0)) != buf + 4
      || memcmp (buf, "ABCDJJJJ", 8))
    abort ();

  __builtin___memset_chk (buf, 'K', sizeof (buf), __builtin_object_size (buf, 0));
  if (__builtin___memmove_chk (buf, data, l1 ? sizeof (buf) : 4, __builtin_object_size (buf, 0)) != buf
      || memcmp (buf, "ABCDKKKK", 8))
    abort ();

  __builtin___memset_chk (buf, 'L', sizeof (buf), __builtin_object_size (buf, 0));

  if (__builtin___snprintf_chk (buf, l1 ? sizeof (buf) : 4, 0, __builtin_object_size (buf, 0), "%d", l1 + 65536) != 5
      || memcmp (buf, "655\0LLLL", 8))
    abort ();






  if (chk_calls)
    abort ();
}

void
main_test (void)
{


  return;

  __asm ("" : "=r" (l1) : "0" (l1));
  test1 ();
}
