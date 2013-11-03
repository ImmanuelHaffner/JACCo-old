












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


const char s0[] = R"(a\u010d\U0000010D\\\'\"\?\a\b\f\n\r\t\v\0\00\000\xa\xabb

c)";
const char s1[] = "a\\\n\\u010d\\U0000010D\\\\\\'\\\"\\?\\a\\b\\f\\n\\r\\t\\v\\0\\00\\000\\xa\\xabb\nc";
const char s2[] = R"*|*(ab

c)"
c)*|"
c)*|*";
const char s3[] = "a\\\nb\nc)\"\nc)*|\"\nc";

const char s4[] = R"(??/
??/
??(??<??=??'??!??-??>??)";
const char s5[] = "?\?/\n?\?/\n?\?(?\?<?\?=?\?'?\?!?\?-?\?>?\?";

const char t0[] = u8R"(a\u010d\U0000010D\\\'\"\?\a\b\f\n\r\t\v\0\00\000\xa\xabb

c)";
const char t1[] = u8"a\\\n\\u010d\\U0000010D\\\\\\'\\\"\\?\\a\\b\\f\\n\\r\\t\\v\\0\\00\\000\\xa\\xabb\nc";
const char t2[] = u8R"*|*(ab

c)"
c)*|"
c)*|*";
const char t3[] = u8"a\\\nb\nc)\"\nc)*|\"\nc";
const char t4[] = u8R"(??/
??/
??(??<??=??'??!??-??>??)";
const char t5[] = u8"?\?/\n?\?/\n?\?(?\?<?\?=?\?'?\?!?\?-?\?>?\?";

const char16_t u0[] = uR"(a\u010d\U0000010D\\\'\"\?\a\b\f\n\r\t\v\0\00\000\xa\xabb

c)";
const char16_t u1[] = u"a\\\n\\u010d\\U0000010D\\\\\\'\\\"\\?\\a\\b\\f\\n\\r\\t\\v\\0\\00\\000\\xa\\xabb\nc";
const char16_t u2[] = uR"*|*(ab

c)"
c)*|"
c)*|*";
const char16_t u3[] = u"a\\\nb\nc)\"\nc)*|\"\nc";
const char16_t u4[] = uR"(??/
??/
??(??<??=??'??!??-??>??)";
const char16_t u5[] = u"?\?/\n?\?/\n?\?(?\?<?\?=?\?'?\?!?\?-?\?>?\?";

const char32_t U0[] = UR"(a\u010d\U0000010D\\\'\"\?\a\b\f\n\r\t\v\0\00\000\xa\xabb

c)";
const char32_t U1[] = U"a\\\n\\u010d\\U0000010D\\\\\\'\\\"\\?\\a\\b\\f\\n\\r\\t\\v\\0\\00\\000\\xa\\xabb\nc";
const char32_t U2[] = UR"*|*(ab

c)"
c)*|"
c)*|*";
const char32_t U3[] = U"a\\\nb\nc)\"\nc)*|\"\nc";
const char32_t U4[] = UR"(??/
??/
??(??<??=??'??!??-??>??)";
const char32_t U5[] = U"?\?/\n?\?/\n?\?(?\?<?\?=?\?'?\?!?\?-?\?>?\?";

const wchar_t L0[] = LR"(a\u010d\U0000010D\\\'\"\?\a\b\f\n\r\t\v\0\00\000\xa\xabb

c)";
const wchar_t L1[] = L"a\\\n\\u010d\\U0000010D\\\\\\'\\\"\\?\\a\\b\\f\\n\\r\\t\\v\\0\\00\\000\\xa\\xabb\nc";
const wchar_t L2[] = LR"*|*(ab

c)"
c)*|"
c)*|*";
const wchar_t L3[] = L"a\\\nb\nc)\"\nc)*|\"\nc";
const wchar_t L4[] = LR"(??/
??/
??(??<??=??'??!??-??>??)";
const wchar_t L5[] = L"?\?/\n?\?/\n?\?(?\?<?\?=?\?'?\?!?\?-?\?>?\?";

int
main (void)
{
  if (sizeof (s0) != sizeof (s1)
      || __builtin_memcmp (s0, s1, sizeof (s0)) != 0)
    __builtin_abort ();
  if (sizeof (s2) != sizeof (s3)
      || __builtin_memcmp (s2, s3, sizeof (s2)) != 0)
    __builtin_abort ();
  if (sizeof (s4) != sizeof (s5)
      || __builtin_memcmp (s4, s5, sizeof (s4)) != 0)
    __builtin_abort ();
  if (sizeof (t0) != sizeof (t1)
      || __builtin_memcmp (t0, t1, sizeof (t0)) != 0)
    __builtin_abort ();
  if (sizeof (t2) != sizeof (t3)
      || __builtin_memcmp (t2, t3, sizeof (t2)) != 0)
    __builtin_abort ();
  if (sizeof (t4) != sizeof (t5)
      || __builtin_memcmp (t4, t5, sizeof (t4)) != 0)
    __builtin_abort ();
  if (sizeof (u0) != sizeof (u1)
      || __builtin_memcmp (u0, u1, sizeof (u0)) != 0)
    __builtin_abort ();
  if (sizeof (u2) != sizeof (u3)
      || __builtin_memcmp (u2, u3, sizeof (u2)) != 0)
    __builtin_abort ();
  if (sizeof (u4) != sizeof (u5)
      || __builtin_memcmp (u4, u5, sizeof (u4)) != 0)
    __builtin_abort ();
  if (sizeof (U0) != sizeof (U1)
      || __builtin_memcmp (U0, U1, sizeof (U0)) != 0)
    __builtin_abort ();
  if (sizeof (U2) != sizeof (U3)
      || __builtin_memcmp (U2, U3, sizeof (U2)) != 0)
    __builtin_abort ();
  if (sizeof (U4) != sizeof (U5)
      || __builtin_memcmp (U4, U5, sizeof (U4)) != 0)
    __builtin_abort ();
  if (sizeof (L0) != sizeof (L1)
      || __builtin_memcmp (L0, L1, sizeof (L0)) != 0)
    __builtin_abort ();
  if (sizeof (L2) != sizeof (L3)
      || __builtin_memcmp (L2, L3, sizeof (L2)) != 0)
    __builtin_abort ();
  if (sizeof (L4) != sizeof (L5)
      || __builtin_memcmp (L4, L5, sizeof (L4)) != 0)
    __builtin_abort ();
  if (sizeof (R"*()*") != 1
      || __builtin_memcmp (R"*()*", "", 1) != 0)
    __builtin_abort ();
  return 0;
}
