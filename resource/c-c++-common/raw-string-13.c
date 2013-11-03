













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
const char s00[] = "??=??(??<??>??)??'??!??-(a)#[{}]^|~";

)??=??";
const char s01[] = "a(
)a"

)a";
const char s02[] = "a(
)a"

)a";
const char s03[] = "ab(
)ab"

)ab";
const char s04[] = "a??/(x)a??/";
const char s05[] = "abcdefghijklmn??(abc)abcdefghijklmn??";
const char s06[] = "abcdefghijklm??/(abc)abcdefghijklm??/";
const char s07[] = "abc(??)abc";)abc";

const char s08[] = "def(de)def";)def";

const char s09[] = "a(??)a"

)a";
const char s10[] = "a(??)a"

)a";
const char s11[] = "ab(??)ab"

)ab";
const char s12[] = "a#(a#)a??=)a#";
const char s13[] = "a#(??)a??=??)a#";
const char s14[] = "??/(x)??/
";)??/";
const char s15[] = "??/(??)??/
";)??/";
const char s16[] = "??(??)??";
const char s17[] = "?(?)??)?";
const char s18[] = "??(??)??)??)??";

const char16_t u00[] = "??=??(??<??>??)??'??!??-(a)#[{}]^|~";

)??=??";
const char16_t u01[] = "a(
)a"

)a";
const char16_t u02[] = "a(
)a"

)a";
const char16_t u03[] = "ab(
)ab"

)ab";
const char16_t u04[] = "a??/(x)a??/";
const char16_t u05[] = "abcdefghijklmn??(abc)abcdefghijklmn??";
const char16_t u06[] = "abcdefghijklm??/(abc)abcdefghijklm??/";
const char16_t u07[] = "abc(??)abc";)abc";

const char16_t u08[] = "def(de)def";)def";

const char16_t u09[] = "a(??)a"

)a";
const char16_t u10[] = "a(??)a"

)a";
const char16_t u11[] = "ab(??)ab"

)ab";
const char16_t u12[] = "a#(a#)a??=)a#";
const char16_t u13[] = "a#(??)a??=??)a#";
const char16_t u14[] = "??/(x)??/
";)??/";
const char16_t u15[] = "??/(??)??/
";)??/";
const char16_t u16[] = "??(??)??";
const char16_t u17[] = "?(?)??)?";
const char16_t u18[] = "??(??)??)??)??";

const char32_t U00[] = "??=??(??<??>??)??'??!??-(a)#[{}]^|~";

)??=??";
const char32_t U01[] = "a(
)a"

)a";
const char32_t U02[] = "a(
)a"

)a";
const char32_t U03[] = "ab(
)ab"

)ab";
const char32_t U04[] = "a??/(x)a??/";
const char32_t U05[] = "abcdefghijklmn??(abc)abcdefghijklmn??";
const char32_t U06[] = "abcdefghijklm??/(abc)abcdefghijklm??/";
const char32_t U07[] = "abc(??)abc";)abc";

const char32_t U08[] = "def(de)def";)def";

const char32_t U09[] = "a(??)a"

)a";
const char32_t U10[] = "a(??)a"

)a";
const char32_t U11[] = "ab(??)ab"

)ab";
const char32_t U12[] = "a#(a#)a??=)a#";
const char32_t U13[] = "a#(??)a??=??)a#";
const char32_t U14[] = "??/(x)??/
";)??/";
const char32_t U15[] = "??/(??)??/
";)??/";
const char32_t U16[] = "??(??)??";
const char32_t U17[] = "?(?)??)?";
const char32_t U18[] = "??(??)??)??)??";

const wchar_t L00[] = "??=??(??<??>??)??'??!??-(a)#[{}]^|~";

)??=??";
const wchar_t L01[] = "a(
)a"

)a";
const wchar_t L02[] = "a(
)a"

)a";
const wchar_t L03[] = "ab(
)ab"

)ab";
const wchar_t L04[] = "a??/(x)a??/";
const wchar_t L05[] = "abcdefghijklmn??(abc)abcdefghijklmn??";
const wchar_t L06[] = "abcdefghijklm??/(abc)abcdefghijklm??/";
const wchar_t L07[] = "abc(??)abc";)abc";

const wchar_t L08[] = "def(de)def";)def";

const wchar_t L09[] = "a(??)a"

)a";
const wchar_t L10[] = "a(??)a"

)a";
const wchar_t L11[] = "ab(??)ab"

)ab";
const wchar_t L12[] = "a#(a#)a??=)a#";
const wchar_t L13[] = "a#(??)a??=??)a#";
const wchar_t L14[] = "??/(x)??/
";)??/";
const wchar_t L15[] = "??/(??)??/
";)??/";
const wchar_t L16[] = "??(??)??";
const wchar_t L17[] = "?(?)??)?";
const wchar_t L18[] = "??(??)??)??)??";

int
main (void)
{




  if (sizeof (s00) != sizeof ("??""<??"">??"")??""'??""!??""-\\\n(a)#[{}]^|~\";\n") || __builtin_memcmp (s00, "??""<??"">??"")??""'??""!??""-\\\n(a)#[{}]^|~\";\n", sizeof (s00)) != 0) __builtin_abort ();
  if (sizeof (s01) != sizeof ("\n)\\\na\"\n") || __builtin_memcmp (s01, "\n)\\\na\"\n", sizeof (s01)) != 0) __builtin_abort ();
  if (sizeof (s02) != sizeof ("\n)a\\\n\"\n") || __builtin_memcmp (s02, "\n)a\\\n\"\n", sizeof (s02)) != 0) __builtin_abort ();
  if (sizeof (s03) != sizeof ("\n)a\\\nb\"\n") || __builtin_memcmp (s03, "\n)a\\\nb\"\n", sizeof (s03)) != 0) __builtin_abort ();
  if (sizeof (s04) != sizeof ("x") || __builtin_memcmp (s04, "x", sizeof (s04)) != 0) __builtin_abort ();
  if (sizeof (s05) != sizeof ("abc") || __builtin_memcmp (s05, "abc", sizeof (s05)) != 0) __builtin_abort ();
  if (sizeof (s06) != sizeof ("abc") || __builtin_memcmp (s06, "abc", sizeof (s06)) != 0) __builtin_abort ();
  if (sizeof (s07) != sizeof ("??"")\\\nabc\";") || __builtin_memcmp (s07, "??"")\\\nabc\";", sizeof (s07)) != 0) __builtin_abort ();
  if (sizeof (s08) != sizeof ("de)\\\ndef\";") || __builtin_memcmp (s08, "de)\\\ndef\";", sizeof (s08)) != 0) __builtin_abort ();
  if (sizeof (s09) != sizeof ("??"")\\\na\"\n") || __builtin_memcmp (s09, "??"")\\\na\"\n", sizeof (s09)) != 0) __builtin_abort ();
  if (sizeof (s10) != sizeof ("??"")a\\\n\"\n") || __builtin_memcmp (s10, "??"")a\\\n\"\n", sizeof (s10)) != 0) __builtin_abort ();
  if (sizeof (s11) != sizeof ("??"")a\\\nb\"\n") || __builtin_memcmp (s11, "??"")a\\\nb\"\n", sizeof (s11)) != 0) __builtin_abort ();
  if (sizeof (s12) != sizeof ("a#)a??""=") || __builtin_memcmp (s12, "a#)a??""=", sizeof (s12)) != 0) __builtin_abort ();
  if (sizeof (s13) != sizeof ("??"")a??""=??") || __builtin_memcmp (s13, "??"")a??""=??", sizeof (s13)) != 0) __builtin_abort ();
  if (sizeof (s14) != sizeof ("x)??""/\n\";") || __builtin_memcmp (s14, "x)??""/\n\";", sizeof (s14)) != 0) __builtin_abort ();
  if (sizeof (s15) != sizeof ("??"")??""/\n\";") || __builtin_memcmp (s15, "??"")??""/\n\";", sizeof (s15)) != 0) __builtin_abort ();
  if (sizeof (s16) != sizeof ("??") || __builtin_memcmp (s16, "??", sizeof (s16)) != 0) __builtin_abort ();
  if (sizeof (s17) != sizeof ("?)??") || __builtin_memcmp (s17, "?)??", sizeof (s17)) != 0) __builtin_abort ();
  if (sizeof (s18) != sizeof ("??"")??"")??") || __builtin_memcmp (s18, "??"")??"")??", sizeof (s18)) != 0) __builtin_abort ();
  if (sizeof (u00) != sizeof ("??""<??"">??"")??""'??""!??""-\\\n(a)#[{}]^|~\";\n") || __builtin_memcmp (u00, "??""<??"">??"")??""'??""!??""-\\\n(a)#[{}]^|~\";\n", sizeof (u00)) != 0) __builtin_abort ();
  if (sizeof (u01) != sizeof ("\n)\\\na\"\n") || __builtin_memcmp (u01, "\n)\\\na\"\n", sizeof (u01)) != 0) __builtin_abort ();
  if (sizeof (u02) != sizeof ("\n)a\\\n\"\n") || __builtin_memcmp (u02, "\n)a\\\n\"\n", sizeof (u02)) != 0) __builtin_abort ();
  if (sizeof (u03) != sizeof ("\n)a\\\nb\"\n") || __builtin_memcmp (u03, "\n)a\\\nb\"\n", sizeof (u03)) != 0) __builtin_abort ();
  if (sizeof (u04) != sizeof ("x") || __builtin_memcmp (u04, "x", sizeof (u04)) != 0) __builtin_abort ();
  if (sizeof (u05) != sizeof ("abc") || __builtin_memcmp (u05, "abc", sizeof (u05)) != 0) __builtin_abort ();
  if (sizeof (u06) != sizeof ("abc") || __builtin_memcmp (u06, "abc", sizeof (u06)) != 0) __builtin_abort ();
  if (sizeof (u07) != sizeof ("??"")\\\nabc\";") || __builtin_memcmp (u07, "??"")\\\nabc\";", sizeof (u07)) != 0) __builtin_abort ();
  if (sizeof (u08) != sizeof ("de)\\\ndef\";") || __builtin_memcmp (u08, "de)\\\ndef\";", sizeof (u08)) != 0) __builtin_abort ();
  if (sizeof (u09) != sizeof ("??"")\\\na\"\n") || __builtin_memcmp (u09, "??"")\\\na\"\n", sizeof (u09)) != 0) __builtin_abort ();
  if (sizeof (u10) != sizeof ("??"")a\\\n\"\n") || __builtin_memcmp (u10, "??"")a\\\n\"\n", sizeof (u10)) != 0) __builtin_abort ();
  if (sizeof (u11) != sizeof ("??"")a\\\nb\"\n") || __builtin_memcmp (u11, "??"")a\\\nb\"\n", sizeof (u11)) != 0) __builtin_abort ();
  if (sizeof (u12) != sizeof ("a#)a??""=") || __builtin_memcmp (u12, "a#)a??""=", sizeof (u12)) != 0) __builtin_abort ();
  if (sizeof (u13) != sizeof ("??"")a??""=??") || __builtin_memcmp (u13, "??"")a??""=??", sizeof (u13)) != 0) __builtin_abort ();
  if (sizeof (u14) != sizeof ("x)??""/\n\";") || __builtin_memcmp (u14, "x)??""/\n\";", sizeof (u14)) != 0) __builtin_abort ();
  if (sizeof (u15) != sizeof ("??"")??""/\n\";") || __builtin_memcmp (u15, "??"")??""/\n\";", sizeof (u15)) != 0) __builtin_abort ();
  if (sizeof (u16) != sizeof ("??") || __builtin_memcmp (u16, "??", sizeof (u16)) != 0) __builtin_abort ();
  if (sizeof (u17) != sizeof ("?)??") || __builtin_memcmp (u17, "?)??", sizeof (u17)) != 0) __builtin_abort ();
  if (sizeof (u18) != sizeof ("??"")??"")??") || __builtin_memcmp (u18, "??"")??"")??", sizeof (u18)) != 0) __builtin_abort ();
  if (sizeof (U00) != sizeof ("??""<??"">??"")??""'??""!??""-\\\n(a)#[{}]^|~\";\n") || __builtin_memcmp (U00, "??""<??"">??"")??""'??""!??""-\\\n(a)#[{}]^|~\";\n", sizeof (U00)) != 0) __builtin_abort ();
  if (sizeof (U01) != sizeof ("\n)\\\na\"\n") || __builtin_memcmp (U01, "\n)\\\na\"\n", sizeof (U01)) != 0) __builtin_abort ();
  if (sizeof (U02) != sizeof ("\n)a\\\n\"\n") || __builtin_memcmp (U02, "\n)a\\\n\"\n", sizeof (U02)) != 0) __builtin_abort ();
  if (sizeof (U03) != sizeof ("\n)a\\\nb\"\n") || __builtin_memcmp (U03, "\n)a\\\nb\"\n", sizeof (U03)) != 0) __builtin_abort ();
  if (sizeof (U04) != sizeof ("x") || __builtin_memcmp (U04, "x", sizeof (U04)) != 0) __builtin_abort ();
  if (sizeof (U05) != sizeof ("abc") || __builtin_memcmp (U05, "abc", sizeof (U05)) != 0) __builtin_abort ();
  if (sizeof (U06) != sizeof ("abc") || __builtin_memcmp (U06, "abc", sizeof (U06)) != 0) __builtin_abort ();
  if (sizeof (U07) != sizeof ("??"")\\\nabc\";") || __builtin_memcmp (U07, "??"")\\\nabc\";", sizeof (U07)) != 0) __builtin_abort ();
  if (sizeof (U08) != sizeof ("de)\\\ndef\";") || __builtin_memcmp (U08, "de)\\\ndef\";", sizeof (U08)) != 0) __builtin_abort ();
  if (sizeof (U09) != sizeof ("??"")\\\na\"\n") || __builtin_memcmp (U09, "??"")\\\na\"\n", sizeof (U09)) != 0) __builtin_abort ();
  if (sizeof (U10) != sizeof ("??"")a\\\n\"\n") || __builtin_memcmp (U10, "??"")a\\\n\"\n", sizeof (U10)) != 0) __builtin_abort ();
  if (sizeof (U11) != sizeof ("??"")a\\\nb\"\n") || __builtin_memcmp (U11, "??"")a\\\nb\"\n", sizeof (U11)) != 0) __builtin_abort ();
  if (sizeof (U12) != sizeof ("a#)a??""=") || __builtin_memcmp (U12, "a#)a??""=", sizeof (U12)) != 0) __builtin_abort ();
  if (sizeof (U13) != sizeof ("??"")a??""=??") || __builtin_memcmp (U13, "??"")a??""=??", sizeof (U13)) != 0) __builtin_abort ();
  if (sizeof (U14) != sizeof ("x)??""/\n\";") || __builtin_memcmp (U14, "x)??""/\n\";", sizeof (U14)) != 0) __builtin_abort ();
  if (sizeof (U15) != sizeof ("??"")??""/\n\";") || __builtin_memcmp (U15, "??"")??""/\n\";", sizeof (U15)) != 0) __builtin_abort ();
  if (sizeof (U16) != sizeof ("??") || __builtin_memcmp (U16, "??", sizeof (U16)) != 0) __builtin_abort ();
  if (sizeof (U17) != sizeof ("?)??") || __builtin_memcmp (U17, "?)??", sizeof (U17)) != 0) __builtin_abort ();
  if (sizeof (U18) != sizeof ("??"")??"")??") || __builtin_memcmp (U18, "??"")??"")??", sizeof (U18)) != 0) __builtin_abort ();
  if (sizeof (L00) != sizeof (L"??""<??"">??"")??""'??""!??""-\\\n(a)#[{}]^|~\";\n") || __builtin_memcmp (L00, L"??""<??"">??"")??""'??""!??""-\\\n(a)#[{}]^|~\";\n", sizeof (L00)) != 0) __builtin_abort ();
  if (sizeof (L01) != sizeof (L"\n)\\\na\"\n") || __builtin_memcmp (L01, L"\n)\\\na\"\n", sizeof (L01)) != 0) __builtin_abort ();
  if (sizeof (L02) != sizeof (L"\n)a\\\n\"\n") || __builtin_memcmp (L02, L"\n)a\\\n\"\n", sizeof (L02)) != 0) __builtin_abort ();
  if (sizeof (L03) != sizeof (L"\n)a\\\nb\"\n") || __builtin_memcmp (L03, L"\n)a\\\nb\"\n", sizeof (L03)) != 0) __builtin_abort ();
  if (sizeof (L04) != sizeof (L"x") || __builtin_memcmp (L04, L"x", sizeof (L04)) != 0) __builtin_abort ();
  if (sizeof (L05) != sizeof (L"abc") || __builtin_memcmp (L05, L"abc", sizeof (L05)) != 0) __builtin_abort ();
  if (sizeof (L06) != sizeof (L"abc") || __builtin_memcmp (L06, L"abc", sizeof (L06)) != 0) __builtin_abort ();
  if (sizeof (L07) != sizeof (L"??"")\\\nabc\";") || __builtin_memcmp (L07, L"??"")\\\nabc\";", sizeof (L07)) != 0) __builtin_abort ();
  if (sizeof (L08) != sizeof (L"de)\\\ndef\";") || __builtin_memcmp (L08, L"de)\\\ndef\";", sizeof (L08)) != 0) __builtin_abort ();
  if (sizeof (L09) != sizeof (L"??"")\\\na\"\n") || __builtin_memcmp (L09, L"??"")\\\na\"\n", sizeof (L09)) != 0) __builtin_abort ();
  if (sizeof (L10) != sizeof (L"??"")a\\\n\"\n") || __builtin_memcmp (L10, L"??"")a\\\n\"\n", sizeof (L10)) != 0) __builtin_abort ();
  if (sizeof (L11) != sizeof (L"??"")a\\\nb\"\n") || __builtin_memcmp (L11, L"??"")a\\\nb\"\n", sizeof (L11)) != 0) __builtin_abort ();
  if (sizeof (L12) != sizeof (L"a#)a??""=") || __builtin_memcmp (L12, L"a#)a??""=", sizeof (L12)) != 0) __builtin_abort ();
  if (sizeof (L13) != sizeof (L"??"")a??""=??") || __builtin_memcmp (L13, L"??"")a??""=??", sizeof (L13)) != 0) __builtin_abort ();
  if (sizeof (L14) != sizeof (L"x)??""/\n\";") || __builtin_memcmp (L14, L"x)??""/\n\";", sizeof (L14)) != 0) __builtin_abort ();
  if (sizeof (L15) != sizeof (L"??"")??""/\n\";") || __builtin_memcmp (L15, L"??"")??""/\n\";", sizeof (L15)) != 0) __builtin_abort ();
  if (sizeof (L16) != sizeof (L"??") || __builtin_memcmp (L16, L"??", sizeof (L16)) != 0) __builtin_abort ();
  if (sizeof (L17) != sizeof (L"?)??") || __builtin_memcmp (L17, L"?)??", sizeof (L17)) != 0) __builtin_abort ();
  if (sizeof (L18) != sizeof (L"??"")??"")??") || __builtin_memcmp (L18, L"??"")??"")??", sizeof (L18)) != 0) __builtin_abort ();
  return 0;
}
