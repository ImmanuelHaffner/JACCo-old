












struct _IO_FILE;



typedef struct _IO_FILE FILE;





typedef struct _IO_FILE __FILE;


typedef __builtin_va_list __gnuc_va_list;

typedef long unsigned int size_t;
typedef int wchar_t;
typedef unsigned int wint_t;
typedef struct
{
  int __count;
  union
  {

    unsigned int __wch;



    char __wchb[4];
  } __value;
} __mbstate_t;


typedef __mbstate_t mbstate_t;






struct tm;









extern wchar_t *wcscpy (wchar_t *__restrict __dest,
   __const wchar_t *__restrict __src) __attribute__ ((__nothrow__ , __leaf__));

extern wchar_t *wcsncpy (wchar_t *__restrict __dest,
    __const wchar_t *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));


extern wchar_t *wcscat (wchar_t *__restrict __dest,
   __const wchar_t *__restrict __src) __attribute__ ((__nothrow__ , __leaf__));

extern wchar_t *wcsncat (wchar_t *__restrict __dest,
    __const wchar_t *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));


extern int wcscmp (__const wchar_t *__s1, __const wchar_t *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));

extern int wcsncmp (__const wchar_t *__s1, __const wchar_t *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));




extern int wcscasecmp (__const wchar_t *__s1, __const wchar_t *__s2) __attribute__ ((__nothrow__ , __leaf__));


extern int wcsncasecmp (__const wchar_t *__s1, __const wchar_t *__s2,
   size_t __n) __attribute__ ((__nothrow__ , __leaf__));



typedef struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;

extern int wcscasecmp_l (__const wchar_t *__s1, __const wchar_t *__s2,
    __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));

extern int wcsncasecmp_l (__const wchar_t *__s1, __const wchar_t *__s2,
     size_t __n, __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));





extern int wcscoll (__const wchar_t *__s1, __const wchar_t *__s2) __attribute__ ((__nothrow__ , __leaf__));



extern size_t wcsxfrm (wchar_t *__restrict __s1,
         __const wchar_t *__restrict __s2, size_t __n) __attribute__ ((__nothrow__ , __leaf__));








extern int wcscoll_l (__const wchar_t *__s1, __const wchar_t *__s2,
        __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));




extern size_t wcsxfrm_l (wchar_t *__s1, __const wchar_t *__s2,
    size_t __n, __locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));


extern wchar_t *wcsdup (__const wchar_t *__s) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__));










extern wchar_t *wcschr (__const wchar_t *__wcs, wchar_t __wc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));
extern wchar_t *wcsrchr (__const wchar_t *__wcs, wchar_t __wc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));





extern size_t wcscspn (__const wchar_t *__wcs, __const wchar_t *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));


extern size_t wcsspn (__const wchar_t *__wcs, __const wchar_t *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));
extern wchar_t *wcspbrk (__const wchar_t *__wcs, __const wchar_t *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));
extern wchar_t *wcsstr (__const wchar_t *__haystack, __const wchar_t *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));



extern wchar_t *wcstok (wchar_t *__restrict __s,
   __const wchar_t *__restrict __delim,
   wchar_t **__restrict __ptr) __attribute__ ((__nothrow__ , __leaf__));


extern size_t wcslen (__const wchar_t *__s) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));

extern size_t wcsnlen (__const wchar_t *__s, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));




extern wchar_t *wmemchr (__const wchar_t *__s, wchar_t __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));



extern int wmemcmp (__const wchar_t *__s1, __const wchar_t *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));


extern wchar_t *wmemcpy (wchar_t *__restrict __s1,
    __const wchar_t *__restrict __s2, size_t __n) __attribute__ ((__nothrow__ , __leaf__));



extern wchar_t *wmemmove (wchar_t *__s1, __const wchar_t *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));


extern wchar_t *wmemset (wchar_t *__s, wchar_t __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__));




extern wint_t btowc (int __c) __attribute__ ((__nothrow__ , __leaf__));



extern int wctob (wint_t __c) __attribute__ ((__nothrow__ , __leaf__));



extern int mbsinit (__const mbstate_t *__ps) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__));



extern size_t mbrtowc (wchar_t *__restrict __pwc,
         __const char *__restrict __s, size_t __n,
         mbstate_t *__p) __attribute__ ((__nothrow__ , __leaf__));


extern size_t wcrtomb (char *__restrict __s, wchar_t __wc,
         mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));


extern size_t __mbrlen (__const char *__restrict __s, size_t __n,
   mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));
extern size_t mbrlen (__const char *__restrict __s, size_t __n,
        mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));




extern size_t mbsrtowcs (wchar_t *__restrict __dst,
    __const char **__restrict __src, size_t __len,
    mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));



extern size_t wcsrtombs (char *__restrict __dst,
    __const wchar_t **__restrict __src, size_t __len,
    mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));






extern size_t mbsnrtowcs (wchar_t *__restrict __dst,
     __const char **__restrict __src, size_t __nmc,
     size_t __len, mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));



extern size_t wcsnrtombs (char *__restrict __dst,
     __const wchar_t **__restrict __src,
     size_t __nwc, size_t __len,
     mbstate_t *__restrict __ps) __attribute__ ((__nothrow__ , __leaf__));



extern double wcstod (__const wchar_t *__restrict __nptr,
        wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));





extern float wcstof (__const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));
extern long double wcstold (__const wchar_t *__restrict __nptr,
       wchar_t **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__));







extern long int wcstol (__const wchar_t *__restrict __nptr,
   wchar_t **__restrict __endptr, int __base) __attribute__ ((__nothrow__ , __leaf__));



extern unsigned long int wcstoul (__const wchar_t *__restrict __nptr,
      wchar_t **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));






__extension__
extern long long int wcstoll (__const wchar_t *__restrict __nptr,
         wchar_t **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__));



__extension__
extern unsigned long long int wcstoull (__const wchar_t *__restrict __nptr,
     wchar_t **__restrict __endptr,
     int __base) __attribute__ ((__nothrow__ , __leaf__));

extern wchar_t *wcpcpy (wchar_t *__restrict __dest,
   __const wchar_t *__restrict __src) __attribute__ ((__nothrow__ , __leaf__));



extern wchar_t *wcpncpy (wchar_t *__restrict __dest,
    __const wchar_t *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));






extern __FILE *open_wmemstream (wchar_t **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__));






extern int fwide (__FILE *__fp, int __mode) __attribute__ ((__nothrow__ , __leaf__));






extern int fwprintf (__FILE *__restrict __stream,
       __const wchar_t *__restrict __format, ...)
                                                           ;




extern int wprintf (__const wchar_t *__restrict __format, ...)
                                                           ;

extern int swprintf (wchar_t *__restrict __s, size_t __n,
       __const wchar_t *__restrict __format, ...)
     __attribute__ ((__nothrow__ , __leaf__)) ;





extern int vfwprintf (__FILE *__restrict __s,
        __const wchar_t *__restrict __format,
        __gnuc_va_list __arg)
                                                           ;




extern int vwprintf (__const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
                                                           ;


extern int vswprintf (wchar_t *__restrict __s, size_t __n,
        __const wchar_t *__restrict __format,
        __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) ;






extern int fwscanf (__FILE *__restrict __stream,
      __const wchar_t *__restrict __format, ...)
                                                          ;




extern int wscanf (__const wchar_t *__restrict __format, ...)
                                                          ;

extern int swscanf (__const wchar_t *__restrict __s,
      __const wchar_t *__restrict __format, ...)
     __attribute__ ((__nothrow__ , __leaf__)) ;
extern int fwscanf (__FILE *__restrict __stream, __const wchar_t *__restrict __format, ...) __asm__ ("" "__isoc99_fwscanf")


                                                          ;
extern int wscanf (__const wchar_t *__restrict __format, ...) __asm__ ("" "__isoc99_wscanf")

                                                          ;
extern int swscanf (__const wchar_t *__restrict __s, __const wchar_t *__restrict __format, ...) __asm__ ("" "__isoc99_swscanf") __attribute__ ((__nothrow__ , __leaf__))


                                                          ;









extern int vfwscanf (__FILE *__restrict __s,
       __const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
                                                          ;




extern int vwscanf (__const wchar_t *__restrict __format,
      __gnuc_va_list __arg)
                                                          ;

extern int vswscanf (__const wchar_t *__restrict __s,
       __const wchar_t *__restrict __format,
       __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) ;





extern int vfwscanf (__FILE *__restrict __s, __const wchar_t *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfwscanf")


                                                          ;
extern int vwscanf (__const wchar_t *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vwscanf")

                                                          ;
extern int vswscanf (__const wchar_t *__restrict __s, __const wchar_t *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vswscanf") __attribute__ ((__nothrow__ , __leaf__))


                                                          ;









extern wint_t fgetwc (__FILE *__stream);
extern wint_t getwc (__FILE *__stream);





extern wint_t getwchar (void);






extern wint_t fputwc (wchar_t __wc, __FILE *__stream);
extern wint_t putwc (wchar_t __wc, __FILE *__stream);





extern wint_t putwchar (wchar_t __wc);







extern wchar_t *fgetws (wchar_t *__restrict __ws, int __n,
   __FILE *__restrict __stream);





extern int fputws (__const wchar_t *__restrict __ws,
     __FILE *__restrict __stream);






extern wint_t ungetwc (wint_t __wc, __FILE *__stream);





extern size_t wcsftime (wchar_t *__restrict __s, size_t __maxsize,
   __const wchar_t *__restrict __format,
   __const struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));



typedef short unsigned int char16_t;
typedef unsigned int char32_t;
const char s00[] = "(a)" "(b)";
const char s01[] = "(a)" "*(b)*";
const char s02[] = "(a)" "(b)";
const char s03[] = "-(a)-" "(b)";
const char s04[] = "(a)" "MNOPQRSTUVWXYZ(b)MNOPQRSTUVWXYZ";
const char s05[] = "(a)" "wxyzABCDEFGHIJKL(b)wxyzABCDEFGHIJKL";
const char s06[] = ";[(a);[" "(b)";
const char s07[] = "(a)" "(b)";
const char s08[] = "(a)" "_{}#[]<>%:;.?*+-(b)_{}#[]<>%:;.?*+-";
const char s09[] = "/^&|~!=,"'(a)/^&|~!=,"'" u8"(b)";
const char s10[] = "(a)" "0123456789abcdef(b)0123456789abcdef";
const char s11[] = "ghijklmnopqrstuv(a)ghijklmnopqrstuv" "w(b)w";

const char16_t u03[] = "-(a)-" "(b)";
const char16_t u04[] = "(a)" "MNOPQRSTUVWXYZ(b)MNOPQRSTUVWXYZ";
const char16_t u05[] = "(a)" "wxyzABCDEFGHIJKL(b)wxyzABCDEFGHIJKL";
const char16_t u06[] = ";[(a);[" "(b)";
const char16_t u07[] = "(a)" "(b)";
const char16_t u08[] = "(a)" "_{}#[]<>%:;.?*+-(b)_{}#[]<>%:;.?*+-";
const char16_t u09[] = "/^&|~!=,"'(a)/^&|~!=,"'" u"(b)";
const char16_t u10[] = "(a)" "0123456789abcdef(b)0123456789abcdef";
const char16_t u11[] = "ghijklmnopqrstuv(a)ghijklmnopqrstuv" "w(b)w";

const char32_t U03[] = "-(a)-" "(b)";
const char32_t U04[] = "(a)" "MNOPQRSTUVWXYZ(b)MNOPQRSTUVWXYZ";
const char32_t U05[] = "(a)" "wxyzABCDEFGHIJKL(b)wxyzABCDEFGHIJKL";
const char32_t U06[] = ";[(a);[" "(b)";
const char32_t U07[] = "(a)" "(b)";
const char32_t U08[] = "(a)" "_{}#[]<>%:;.?*+-(b)_{}#[]<>%:;.?*+-";
const char32_t U09[] = "/^&|~!=,"'(a)/^&|~!=,"'" U"(b)";
const char32_t U10[] = "(a)" "0123456789abcdef(b)0123456789abcdef";
const char32_t U11[] = "ghijklmnopqrstuv(a)ghijklmnopqrstuv" "w(b)w";

const wchar_t L03[] = "-(a)-" L"(b)";
const wchar_t L04[] = "(a)" "MNOPQRSTUVWXYZ(b)MNOPQRSTUVWXYZ";
const wchar_t L05[] = "(a)" "wxyzABCDEFGHIJKL(b)wxyzABCDEFGHIJKL";
const wchar_t L06[] = ";[(a);[" "(b)";
const wchar_t L07[] = L"(a)" "(b)";
const wchar_t L08[] = "(a)" "_{}#[]<>%:;.?*+-(b)_{}#[]<>%:;.?*+-";
const wchar_t L09[] = "/^&|~!=,"'(a)/^&|~!=,"'" L"(b)";
const wchar_t L10[] = L"(a)" "0123456789abcdef(b)0123456789abcdef";
const wchar_t L11[] = "ghijklmnopqrstuv(a)ghijklmnopqrstuv" "w(b)w";

int
main (void)
{




  if (sizeof (s00) != sizeof ("a(b)") || __builtin_memcmp (s00, "a(b)", sizeof (s00)) != 0) __builtin_abort ();
  if (sizeof (s01) != sizeof ("(a)b") || __builtin_memcmp (s01, "(a)b", sizeof (s01)) != 0) __builtin_abort ();
  if (sizeof (s02) != sizeof ("ab") || __builtin_memcmp (s02, "ab", sizeof (s02)) != 0) __builtin_abort ();
  if (sizeof (s03) != sizeof ("a(b)") || __builtin_memcmp (s03, "a(b)", sizeof (s03)) != 0) __builtin_abort ();
  if (sizeof (s04) != sizeof ("(a)b") || __builtin_memcmp (s04, "(a)b", sizeof (s04)) != 0) __builtin_abort ();
  if (sizeof (s05) != sizeof ("ab") || __builtin_memcmp (s05, "ab", sizeof (s05)) != 0) __builtin_abort ();
  if (sizeof (s06) != sizeof ("a(b)") || __builtin_memcmp (s06, "a(b)", sizeof (s06)) != 0) __builtin_abort ();
  if (sizeof (s07) != sizeof ("(a)b") || __builtin_memcmp (s07, "(a)b", sizeof (s07)) != 0) __builtin_abort ();
  if (sizeof (s08) != sizeof ("ab") || __builtin_memcmp (s08, "ab", sizeof (s08)) != 0) __builtin_abort ();
  if (sizeof (s09) != sizeof ("a(b)") || __builtin_memcmp (s09, "a(b)", sizeof (s09)) != 0) __builtin_abort ();
  if (sizeof (s10) != sizeof ("(a)b") || __builtin_memcmp (s10, "(a)b", sizeof (s10)) != 0) __builtin_abort ();
  if (sizeof (s11) != sizeof ("ab") || __builtin_memcmp (s11, "ab", sizeof (s11)) != 0) __builtin_abort ();
  if (sizeof (u03) != sizeof ("a(b)") || __builtin_memcmp (u03, "a(b)", sizeof (u03)) != 0) __builtin_abort ();
  if (sizeof (u04) != sizeof ("(a)b") || __builtin_memcmp (u04, "(a)b", sizeof (u04)) != 0) __builtin_abort ();
  if (sizeof (u05) != sizeof ("ab") || __builtin_memcmp (u05, "ab", sizeof (u05)) != 0) __builtin_abort ();
  if (sizeof (u06) != sizeof ("a(b)") || __builtin_memcmp (u06, "a(b)", sizeof (u06)) != 0) __builtin_abort ();
  if (sizeof (u07) != sizeof ("(a)b") || __builtin_memcmp (u07, "(a)b", sizeof (u07)) != 0) __builtin_abort ();
  if (sizeof (u08) != sizeof ("ab") || __builtin_memcmp (u08, "ab", sizeof (u08)) != 0) __builtin_abort ();
  if (sizeof (u09) != sizeof ("a(b)") || __builtin_memcmp (u09, "a(b)", sizeof (u09)) != 0) __builtin_abort ();
  if (sizeof (u10) != sizeof ("(a)b") || __builtin_memcmp (u10, "(a)b", sizeof (u10)) != 0) __builtin_abort ();
  if (sizeof (u11) != sizeof ("ab") || __builtin_memcmp (u11, "ab", sizeof (u11)) != 0) __builtin_abort ();
  if (sizeof (U03) != sizeof ("a(b)") || __builtin_memcmp (U03, "a(b)", sizeof (U03)) != 0) __builtin_abort ();
  if (sizeof (U04) != sizeof ("(a)b") || __builtin_memcmp (U04, "(a)b", sizeof (U04)) != 0) __builtin_abort ();
  if (sizeof (U05) != sizeof ("ab") || __builtin_memcmp (U05, "ab", sizeof (U05)) != 0) __builtin_abort ();
  if (sizeof (U06) != sizeof ("a(b)") || __builtin_memcmp (U06, "a(b)", sizeof (U06)) != 0) __builtin_abort ();
  if (sizeof (U07) != sizeof ("(a)b") || __builtin_memcmp (U07, "(a)b", sizeof (U07)) != 0) __builtin_abort ();
  if (sizeof (U08) != sizeof ("ab") || __builtin_memcmp (U08, "ab", sizeof (U08)) != 0) __builtin_abort ();
  if (sizeof (U09) != sizeof ("a(b)") || __builtin_memcmp (U09, "a(b)", sizeof (U09)) != 0) __builtin_abort ();
  if (sizeof (U10) != sizeof ("(a)b") || __builtin_memcmp (U10, "(a)b", sizeof (U10)) != 0) __builtin_abort ();
  if (sizeof (U11) != sizeof ("ab") || __builtin_memcmp (U11, "ab", sizeof (U11)) != 0) __builtin_abort ();
  if (sizeof (L03) != sizeof (L"a(b)") || __builtin_memcmp (L03, L"a(b)", sizeof (L03)) != 0) __builtin_abort ();
  if (sizeof (L04) != sizeof (L"(a)b") || __builtin_memcmp (L04, L"(a)b", sizeof (L04)) != 0) __builtin_abort ();
  if (sizeof (L05) != sizeof (L"ab") || __builtin_memcmp (L05, L"ab", sizeof (L05)) != 0) __builtin_abort ();
  if (sizeof (L06) != sizeof (L"a(b)") || __builtin_memcmp (L06, L"a(b)", sizeof (L06)) != 0) __builtin_abort ();
  if (sizeof (L07) != sizeof (L"(a)b") || __builtin_memcmp (L07, L"(a)b", sizeof (L07)) != 0) __builtin_abort ();
  if (sizeof (L08) != sizeof (L"ab") || __builtin_memcmp (L08, L"ab", sizeof (L08)) != 0) __builtin_abort ();
  if (sizeof (L09) != sizeof (L"a(b)") || __builtin_memcmp (L09, L"a(b)", sizeof (L09)) != 0) __builtin_abort ();
  if (sizeof (L10) != sizeof (L"(a)b") || __builtin_memcmp (L10, L"(a)b", sizeof (L10)) != 0) __builtin_abort ();
  if (sizeof (L11) != sizeof (L"ab") || __builtin_memcmp (L11, L"ab", sizeof (L11)) != 0) __builtin_abort ();
  return 0;
}
