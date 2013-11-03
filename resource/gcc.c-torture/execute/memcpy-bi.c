













typedef long unsigned int size_t;









extern void *memcpy (void *__restrict __dest,
       __const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, __const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));






extern void *memccpy (void *__restrict __dest, __const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (__const void *__s1, __const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memchr (__const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern char *strcpy (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, __const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (__const char *__s1, __const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (__const char *__s1, __const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (__const char *__s1, __const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));






typedef struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;


extern int strcoll_l (__const char *__s1, __const char *__s2, __locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));

extern size_t strxfrm_l (char *__dest, __const char *__src, size_t __n,
    __locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));





extern char *strdup (__const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (__const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));

extern char *strchr (__const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strrchr (__const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern size_t strcspn (__const char *__s, __const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (__const char *__s, __const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strpbrk (__const char *__s, __const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strstr (__const char *__haystack, __const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strtok (char *__restrict __s, __const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));




extern char *__strtok_r (char *__restrict __s,
    __const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, __const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));


extern size_t strlen (__const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern size_t strnlen (__const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));

extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__ , __leaf__))

                        __attribute__ ((__nonnull__ (2)));
extern char *strerror_l (int __errnum, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));





extern void __bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern void bcopy (__const void *__src, void *__dest, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int bcmp (__const void *__s1, __const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *index (__const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *rindex (__const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int strcasecmp (__const char *__s1, __const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (__const char *__s1, __const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strsep (char **__restrict __stringp,
       __const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));


extern char *__stpcpy (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, __const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        __const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




char src[80] __attribute__ ((aligned));
char dst[80] __attribute__ ((aligned));

void
check (char *test, char *match, int n)
{
  if (memcmp (test, match, n))
    abort ();
}
main ()
{
  int i,j;

  for (i = 0; i < sizeof (src); ++i)
      src[i] = 'a' + i % 26;

  { memset (dst, 0, 0); memcpy (dst, src, 0); check (dst, src, 0); } { memset (dst, 0, (0) + 1); memcpy (dst, src, (0) + 1); check (dst, src, (0) + 1); } { memset (dst, 0, (0) + 2); memcpy (dst, src, (0) + 2); check (dst, src, (0) + 2); } { memset (dst, 0, (0) + 3); memcpy (dst, src, (0) + 3); check (dst, src, (0) + 3); };
  { memset (dst, 0, 4); memcpy (dst, src, 4); check (dst, src, 4); } { memset (dst, 0, (4) + 1); memcpy (dst, src, (4) + 1); check (dst, src, (4) + 1); } { memset (dst, 0, (4) + 2); memcpy (dst, src, (4) + 2); check (dst, src, (4) + 2); } { memset (dst, 0, (4) + 3); memcpy (dst, src, (4) + 3); check (dst, src, (4) + 3); };
  { memset (dst, 0, 8); memcpy (dst, src, 8); check (dst, src, 8); } { memset (dst, 0, (8) + 1); memcpy (dst, src, (8) + 1); check (dst, src, (8) + 1); } { memset (dst, 0, (8) + 2); memcpy (dst, src, (8) + 2); check (dst, src, (8) + 2); } { memset (dst, 0, (8) + 3); memcpy (dst, src, (8) + 3); check (dst, src, (8) + 3); };
  { memset (dst, 0, 12); memcpy (dst, src, 12); check (dst, src, 12); } { memset (dst, 0, (12) + 1); memcpy (dst, src, (12) + 1); check (dst, src, (12) + 1); } { memset (dst, 0, (12) + 2); memcpy (dst, src, (12) + 2); check (dst, src, (12) + 2); } { memset (dst, 0, (12) + 3); memcpy (dst, src, (12) + 3); check (dst, src, (12) + 3); };
  { memset (dst, 0, 16); memcpy (dst, src, 16); check (dst, src, 16); } { memset (dst, 0, (16) + 1); memcpy (dst, src, (16) + 1); check (dst, src, (16) + 1); } { memset (dst, 0, (16) + 2); memcpy (dst, src, (16) + 2); check (dst, src, (16) + 2); } { memset (dst, 0, (16) + 3); memcpy (dst, src, (16) + 3); check (dst, src, (16) + 3); };
  { memset (dst, 0, 20); memcpy (dst, src, 20); check (dst, src, 20); } { memset (dst, 0, (20) + 1); memcpy (dst, src, (20) + 1); check (dst, src, (20) + 1); } { memset (dst, 0, (20) + 2); memcpy (dst, src, (20) + 2); check (dst, src, (20) + 2); } { memset (dst, 0, (20) + 3); memcpy (dst, src, (20) + 3); check (dst, src, (20) + 3); };
  { memset (dst, 0, 24); memcpy (dst, src, 24); check (dst, src, 24); } { memset (dst, 0, (24) + 1); memcpy (dst, src, (24) + 1); check (dst, src, (24) + 1); } { memset (dst, 0, (24) + 2); memcpy (dst, src, (24) + 2); check (dst, src, (24) + 2); } { memset (dst, 0, (24) + 3); memcpy (dst, src, (24) + 3); check (dst, src, (24) + 3); };
  { memset (dst, 0, 28); memcpy (dst, src, 28); check (dst, src, 28); } { memset (dst, 0, (28) + 1); memcpy (dst, src, (28) + 1); check (dst, src, (28) + 1); } { memset (dst, 0, (28) + 2); memcpy (dst, src, (28) + 2); check (dst, src, (28) + 2); } { memset (dst, 0, (28) + 3); memcpy (dst, src, (28) + 3); check (dst, src, (28) + 3); };
  { memset (dst, 0, 32); memcpy (dst, src, 32); check (dst, src, 32); } { memset (dst, 0, (32) + 1); memcpy (dst, src, (32) + 1); check (dst, src, (32) + 1); } { memset (dst, 0, (32) + 2); memcpy (dst, src, (32) + 2); check (dst, src, (32) + 2); } { memset (dst, 0, (32) + 3); memcpy (dst, src, (32) + 3); check (dst, src, (32) + 3); };
  { memset (dst, 0, 36); memcpy (dst, src, 36); check (dst, src, 36); } { memset (dst, 0, (36) + 1); memcpy (dst, src, (36) + 1); check (dst, src, (36) + 1); } { memset (dst, 0, (36) + 2); memcpy (dst, src, (36) + 2); check (dst, src, (36) + 2); } { memset (dst, 0, (36) + 3); memcpy (dst, src, (36) + 3); check (dst, src, (36) + 3); };
  { memset (dst, 0, 40); memcpy (dst, src, 40); check (dst, src, 40); } { memset (dst, 0, (40) + 1); memcpy (dst, src, (40) + 1); check (dst, src, (40) + 1); } { memset (dst, 0, (40) + 2); memcpy (dst, src, (40) + 2); check (dst, src, (40) + 2); } { memset (dst, 0, (40) + 3); memcpy (dst, src, (40) + 3); check (dst, src, (40) + 3); };
  { memset (dst, 0, 44); memcpy (dst, src, 44); check (dst, src, 44); } { memset (dst, 0, (44) + 1); memcpy (dst, src, (44) + 1); check (dst, src, (44) + 1); } { memset (dst, 0, (44) + 2); memcpy (dst, src, (44) + 2); check (dst, src, (44) + 2); } { memset (dst, 0, (44) + 3); memcpy (dst, src, (44) + 3); check (dst, src, (44) + 3); };
  { memset (dst, 0, 48); memcpy (dst, src, 48); check (dst, src, 48); } { memset (dst, 0, (48) + 1); memcpy (dst, src, (48) + 1); check (dst, src, (48) + 1); } { memset (dst, 0, (48) + 2); memcpy (dst, src, (48) + 2); check (dst, src, (48) + 2); } { memset (dst, 0, (48) + 3); memcpy (dst, src, (48) + 3); check (dst, src, (48) + 3); };
  { memset (dst, 0, 52); memcpy (dst, src, 52); check (dst, src, 52); } { memset (dst, 0, (52) + 1); memcpy (dst, src, (52) + 1); check (dst, src, (52) + 1); } { memset (dst, 0, (52) + 2); memcpy (dst, src, (52) + 2); check (dst, src, (52) + 2); } { memset (dst, 0, (52) + 3); memcpy (dst, src, (52) + 3); check (dst, src, (52) + 3); };
  { memset (dst, 0, 56); memcpy (dst, src, 56); check (dst, src, 56); } { memset (dst, 0, (56) + 1); memcpy (dst, src, (56) + 1); check (dst, src, (56) + 1); } { memset (dst, 0, (56) + 2); memcpy (dst, src, (56) + 2); check (dst, src, (56) + 2); } { memset (dst, 0, (56) + 3); memcpy (dst, src, (56) + 3); check (dst, src, (56) + 3); };
  { memset (dst, 0, 60); memcpy (dst, src, 60); check (dst, src, 60); } { memset (dst, 0, (60) + 1); memcpy (dst, src, (60) + 1); check (dst, src, (60) + 1); } { memset (dst, 0, (60) + 2); memcpy (dst, src, (60) + 2); check (dst, src, (60) + 2); } { memset (dst, 0, (60) + 3); memcpy (dst, src, (60) + 3); check (dst, src, (60) + 3); };
  { memset (dst, 0, 64); memcpy (dst, src, 64); check (dst, src, 64); } { memset (dst, 0, (64) + 1); memcpy (dst, src, (64) + 1); check (dst, src, (64) + 1); } { memset (dst, 0, (64) + 2); memcpy (dst, src, (64) + 2); check (dst, src, (64) + 2); } { memset (dst, 0, (64) + 3); memcpy (dst, src, (64) + 3); check (dst, src, (64) + 3); };
  { memset (dst, 0, 68); memcpy (dst, src, 68); check (dst, src, 68); } { memset (dst, 0, (68) + 1); memcpy (dst, src, (68) + 1); check (dst, src, (68) + 1); } { memset (dst, 0, (68) + 2); memcpy (dst, src, (68) + 2); check (dst, src, (68) + 2); } { memset (dst, 0, (68) + 3); memcpy (dst, src, (68) + 3); check (dst, src, (68) + 3); };
  { memset (dst, 0, 72); memcpy (dst, src, 72); check (dst, src, 72); } { memset (dst, 0, (72) + 1); memcpy (dst, src, (72) + 1); check (dst, src, (72) + 1); } { memset (dst, 0, (72) + 2); memcpy (dst, src, (72) + 2); check (dst, src, (72) + 2); } { memset (dst, 0, (72) + 3); memcpy (dst, src, (72) + 3); check (dst, src, (72) + 3); };
  { memset (dst, 0, 76); memcpy (dst, src, 76); check (dst, src, 76); } { memset (dst, 0, (76) + 1); memcpy (dst, src, (76) + 1); check (dst, src, (76) + 1); } { memset (dst, 0, (76) + 2); memcpy (dst, src, (76) + 2); check (dst, src, (76) + 2); } { memset (dst, 0, (76) + 3); memcpy (dst, src, (76) + 3); check (dst, src, (76) + 3); };

  return 0;
}
