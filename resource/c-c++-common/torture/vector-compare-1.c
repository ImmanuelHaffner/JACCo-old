int main (int argc, char *argv[]) {

    __attribute__((vector_size((4)*sizeof(int)))) int i0;
    __attribute__((vector_size((4)*sizeof(int)))) int i1;
    __attribute__((vector_size((4)*sizeof(int)))) int ires;
    int i;

    i0 = (__attribute__((vector_size((4)*sizeof(int)))) int){(int)argc, 1, 2, 10};
    i1 = (__attribute__((vector_size((4)*sizeof(int)))) int){0, 3, 2, (int)-23};
    ; do { ires = (i0 > i1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ires)[__i] != ((i0)[__i] > (i1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " ">" " " "%i" " ? -1 : 0) ", (ires)[__i], (i0)[__i], (i1)[__i]); __builtin_abort (); } } } while (0); ires = (i0 < i1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ires)[__i] != ((i0)[__i] < (i1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "<" " " "%i" " ? -1 : 0) ", (ires)[__i], (i0)[__i], (i1)[__i]); __builtin_abort (); } } } while (0); ires = (i0 >= i1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ires)[__i] != ((i0)[__i] >= (i1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " ">=" " " "%i" " ? -1 : 0) ", (ires)[__i], (i0)[__i], (i1)[__i]); __builtin_abort (); } } } while (0); ires = (i0 <= i1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ires)[__i] != ((i0)[__i] <= (i1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "<=" " " "%i" " ? -1 : 0) ", (ires)[__i], (i0)[__i], (i1)[__i]); __builtin_abort (); } } } while (0); ires = (i0 == i1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ires)[__i] != ((i0)[__i] == (i1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "==" " " "%i" " ? -1 : 0) ", (ires)[__i], (i0)[__i], (i1)[__i]); __builtin_abort (); } } } while (0); ires = (i0 != i1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ires)[__i] != ((i0)[__i] != (i1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "!=" " " "%i" " ? -1 : 0) ", (ires)[__i], (i0)[__i], (i1)[__i]); __builtin_abort (); } } } while (0); } while (0);



    __attribute__((vector_size((4)*sizeof(int)))) int ures;
    __attribute__((vector_size((4)*sizeof(unsigned int)))) unsigned int u0;
    __attribute__((vector_size((4)*sizeof(unsigned int)))) unsigned int u1;

    u0 = (__attribute__((vector_size((4)*sizeof(unsigned int)))) unsigned int){(unsigned int)argc, 1, 2, 10};
    u1 = (__attribute__((vector_size((4)*sizeof(unsigned int)))) unsigned int){0, 3, 2, (unsigned int)-23};
    ; do { ures = (u0 > u1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ures)[__i] != ((u0)[__i] > (u1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " ">" " " "%u" " ? -1 : 0) ", (ures)[__i], (u0)[__i], (u1)[__i]); __builtin_abort (); } } } while (0); ures = (u0 < u1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ures)[__i] != ((u0)[__i] < (u1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "<" " " "%u" " ? -1 : 0) ", (ures)[__i], (u0)[__i], (u1)[__i]); __builtin_abort (); } } } while (0); ures = (u0 >= u1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ures)[__i] != ((u0)[__i] >= (u1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " ">=" " " "%u" " ? -1 : 0) ", (ures)[__i], (u0)[__i], (u1)[__i]); __builtin_abort (); } } } while (0); ures = (u0 <= u1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ures)[__i] != ((u0)[__i] <= (u1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "<=" " " "%u" " ? -1 : 0) ", (ures)[__i], (u0)[__i], (u1)[__i]); __builtin_abort (); } } } while (0); ures = (u0 == u1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ures)[__i] != ((u0)[__i] == (u1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "==" " " "%u" " ? -1 : 0) ", (ures)[__i], (u0)[__i], (u1)[__i]); __builtin_abort (); } } } while (0); ures = (u0 != u1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ures)[__i] != ((u0)[__i] != (u1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "!=" " " "%u" " ? -1 : 0) ", (ures)[__i], (u0)[__i], (u1)[__i]); __builtin_abort (); } } } while (0); } while (0);




    __attribute__((vector_size((8)*sizeof(short)))) short s0;
    __attribute__((vector_size((8)*sizeof(short)))) short s1;
    __attribute__((vector_size((8)*sizeof(short)))) short sres;

    s0 = (__attribute__((vector_size((8)*sizeof(short)))) short){(short)argc, 1, 2, 10, 6, 87, (short)-5, 2};
    s1 = (__attribute__((vector_size((8)*sizeof(short)))) short){0, 3, 2, (short)-23, 12, 10, (short)-2, 0};
    ; do { sres = (s0 > s1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((sres)[__i] != ((s0)[__i] > (s1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " ">" " " "%i" " ? -1 : 0) ", (sres)[__i], (s0)[__i], (s1)[__i]); __builtin_abort (); } } } while (0); sres = (s0 < s1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((sres)[__i] != ((s0)[__i] < (s1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "<" " " "%i" " ? -1 : 0) ", (sres)[__i], (s0)[__i], (s1)[__i]); __builtin_abort (); } } } while (0); sres = (s0 >= s1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((sres)[__i] != ((s0)[__i] >= (s1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " ">=" " " "%i" " ? -1 : 0) ", (sres)[__i], (s0)[__i], (s1)[__i]); __builtin_abort (); } } } while (0); sres = (s0 <= s1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((sres)[__i] != ((s0)[__i] <= (s1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "<=" " " "%i" " ? -1 : 0) ", (sres)[__i], (s0)[__i], (s1)[__i]); __builtin_abort (); } } } while (0); sres = (s0 == s1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((sres)[__i] != ((s0)[__i] == (s1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "==" " " "%i" " ? -1 : 0) ", (sres)[__i], (s0)[__i], (s1)[__i]); __builtin_abort (); } } } while (0); sres = (s0 != s1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((sres)[__i] != ((s0)[__i] != (s1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "!=" " " "%i" " ? -1 : 0) ", (sres)[__i], (s0)[__i], (s1)[__i]); __builtin_abort (); } } } while (0); } while (0);



    __attribute__((vector_size((8)*sizeof(unsigned short)))) unsigned short us0;
    __attribute__((vector_size((8)*sizeof(unsigned short)))) unsigned short us1;
    __attribute__((vector_size((8)*sizeof(short)))) short usres;

    us0 = (__attribute__((vector_size((8)*sizeof(unsigned short)))) unsigned short){(unsigned short)argc, 1, 2, 10, 6, 87, (unsigned short)-5, 2};
    us1 = (__attribute__((vector_size((8)*sizeof(unsigned short)))) unsigned short){0, 3, 2, (unsigned short)-23, 12, 10, (unsigned short)-2, 0};
    ; do { usres = (us0 > us1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((usres)[__i] != ((us0)[__i] > (us1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " ">" " " "%u" " ? -1 : 0) ", (usres)[__i], (us0)[__i], (us1)[__i]); __builtin_abort (); } } } while (0); usres = (us0 < us1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((usres)[__i] != ((us0)[__i] < (us1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "<" " " "%u" " ? -1 : 0) ", (usres)[__i], (us0)[__i], (us1)[__i]); __builtin_abort (); } } } while (0); usres = (us0 >= us1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((usres)[__i] != ((us0)[__i] >= (us1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " ">=" " " "%u" " ? -1 : 0) ", (usres)[__i], (us0)[__i], (us1)[__i]); __builtin_abort (); } } } while (0); usres = (us0 <= us1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((usres)[__i] != ((us0)[__i] <= (us1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "<=" " " "%u" " ? -1 : 0) ", (usres)[__i], (us0)[__i], (us1)[__i]); __builtin_abort (); } } } while (0); usres = (us0 == us1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((usres)[__i] != ((us0)[__i] == (us1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "==" " " "%u" " ? -1 : 0) ", (usres)[__i], (us0)[__i], (us1)[__i]); __builtin_abort (); } } } while (0); usres = (us0 != us1); do { int __i; for (__i = 0; __i < 8; __i ++) { if ((usres)[__i] != ((us0)[__i] != (us1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "!=" " " "%u" " ? -1 : 0) ", (usres)[__i], (us0)[__i], (us1)[__i]); __builtin_abort (); } } } while (0); } while (0);



    __attribute__((vector_size((16)*sizeof(signed char)))) signed char c0;
    __attribute__((vector_size((16)*sizeof(signed char)))) signed char c1;
    __attribute__((vector_size((16)*sizeof(signed char)))) signed char cres;

    c0 = (__attribute__((vector_size((16)*sizeof(signed char)))) signed char){(signed char)argc, 1, 2, 10, 6, 87, (signed char)-5, 2,
                             (signed char)argc, 1, 2, 10, 6, 87, (signed char)-5, 2 };

    c1 = (__attribute__((vector_size((16)*sizeof(signed char)))) signed char){0, 3, 2, (signed char)-23, 12, 10, (signed char)-2, 0,
                             0, 3, 2, (signed char)-23, 12, 10, (signed char)-2, 0};
    ; do { cres = (c0 > c1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((cres)[__i] != ((c0)[__i] > (c1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " ">" " " "%i" " ? -1 : 0) ", (cres)[__i], (c0)[__i], (c1)[__i]); __builtin_abort (); } } } while (0); cres = (c0 < c1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((cres)[__i] != ((c0)[__i] < (c1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "<" " " "%i" " ? -1 : 0) ", (cres)[__i], (c0)[__i], (c1)[__i]); __builtin_abort (); } } } while (0); cres = (c0 >= c1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((cres)[__i] != ((c0)[__i] >= (c1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " ">=" " " "%i" " ? -1 : 0) ", (cres)[__i], (c0)[__i], (c1)[__i]); __builtin_abort (); } } } while (0); cres = (c0 <= c1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((cres)[__i] != ((c0)[__i] <= (c1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "<=" " " "%i" " ? -1 : 0) ", (cres)[__i], (c0)[__i], (c1)[__i]); __builtin_abort (); } } } while (0); cres = (c0 == c1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((cres)[__i] != ((c0)[__i] == (c1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "==" " " "%i" " ? -1 : 0) ", (cres)[__i], (c0)[__i], (c1)[__i]); __builtin_abort (); } } } while (0); cres = (c0 != c1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((cres)[__i] != ((c0)[__i] != (c1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%i" " " "!=" " " "%i" " ? -1 : 0) ", (cres)[__i], (c0)[__i], (c1)[__i]); __builtin_abort (); } } } while (0); } while (0);



    __attribute__((vector_size((16)*sizeof(unsigned char)))) unsigned char uc0;
    __attribute__((vector_size((16)*sizeof(unsigned char)))) unsigned char uc1;
    __attribute__((vector_size((16)*sizeof(signed char)))) signed char ucres;

    uc0 = (__attribute__((vector_size((16)*sizeof(unsigned char)))) unsigned char){(unsigned char)argc, 1, 2, 10, 6, 87, (unsigned char)-5, 2,
                              (unsigned char)argc, 1, 2, 10, 6, 87, (unsigned char)-5, 2 };

    uc1 = (__attribute__((vector_size((16)*sizeof(unsigned char)))) unsigned char){0, 3, 2, (unsigned char)-23, 12, 10, (unsigned char)-2, 0,
                             0, 3, 2, (unsigned char)-23, 12, 10, (unsigned char)-2, 0};
    ; do { ucres = (uc0 > uc1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((ucres)[__i] != ((uc0)[__i] > (uc1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " ">" " " "%u" " ? -1 : 0) ", (ucres)[__i], (uc0)[__i], (uc1)[__i]); __builtin_abort (); } } } while (0); ucres = (uc0 < uc1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((ucres)[__i] != ((uc0)[__i] < (uc1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "<" " " "%u" " ? -1 : 0) ", (ucres)[__i], (uc0)[__i], (uc1)[__i]); __builtin_abort (); } } } while (0); ucres = (uc0 >= uc1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((ucres)[__i] != ((uc0)[__i] >= (uc1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " ">=" " " "%u" " ? -1 : 0) ", (ucres)[__i], (uc0)[__i], (uc1)[__i]); __builtin_abort (); } } } while (0); ucres = (uc0 <= uc1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((ucres)[__i] != ((uc0)[__i] <= (uc1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "<=" " " "%u" " ? -1 : 0) ", (ucres)[__i], (uc0)[__i], (uc1)[__i]); __builtin_abort (); } } } while (0); ucres = (uc0 == uc1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((ucres)[__i] != ((uc0)[__i] == (uc1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "==" " " "%u" " ? -1 : 0) ", (ucres)[__i], (uc0)[__i], (uc1)[__i]); __builtin_abort (); } } } while (0); ucres = (uc0 != uc1); do { int __i; for (__i = 0; __i < 16; __i ++) { if ((ucres)[__i] != ((uc0)[__i] != (uc1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%u" " " "!=" " " "%u" " ? -1 : 0) ", (ucres)[__i], (uc0)[__i], (uc1)[__i]); __builtin_abort (); } } } while (0); } while (0);


    __attribute__((vector_size((4)*sizeof(float)))) float f0;
    __attribute__((vector_size((4)*sizeof(float)))) float f1;
    __typeof (f0 == f1) ifres;

    f0 = (__attribute__((vector_size((4)*sizeof(float)))) float){(float)argc, 1., 2., 10.};
    f1 = (__attribute__((vector_size((4)*sizeof(float)))) float){0., 3., 2., (float)-23};
    ; do { ifres = (f0 > f1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ifres)[__i] != ((f0)[__i] > (f1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " ">" " " "%f" " ? -1 : 0) ", (ifres)[__i], (f0)[__i], (f1)[__i]); __builtin_abort (); } } } while (0); ifres = (f0 < f1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ifres)[__i] != ((f0)[__i] < (f1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " "<" " " "%f" " ? -1 : 0) ", (ifres)[__i], (f0)[__i], (f1)[__i]); __builtin_abort (); } } } while (0); ifres = (f0 >= f1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ifres)[__i] != ((f0)[__i] >= (f1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " ">=" " " "%f" " ? -1 : 0) ", (ifres)[__i], (f0)[__i], (f1)[__i]); __builtin_abort (); } } } while (0); ifres = (f0 <= f1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ifres)[__i] != ((f0)[__i] <= (f1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " "<=" " " "%f" " ? -1 : 0) ", (ifres)[__i], (f0)[__i], (f1)[__i]); __builtin_abort (); } } } while (0); ifres = (f0 == f1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ifres)[__i] != ((f0)[__i] == (f1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " "==" " " "%f" " ? -1 : 0) ", (ifres)[__i], (f0)[__i], (f1)[__i]); __builtin_abort (); } } } while (0); ifres = (f0 != f1); do { int __i; for (__i = 0; __i < 4; __i ++) { if ((ifres)[__i] != ((f0)[__i] != (f1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " "!=" " " "%f" " ? -1 : 0) ", (ifres)[__i], (f0)[__i], (f1)[__i]); __builtin_abort (); } } } while (0); } while (0);


    __attribute__((vector_size((2)*sizeof(double)))) double d0;
    __attribute__((vector_size((2)*sizeof(double)))) double d1;
    __typeof (d0 == d1) idres;

    d0 = (__attribute__((vector_size((2)*sizeof(double)))) double){(double)argc, 10.};
    d1 = (__attribute__((vector_size((2)*sizeof(double)))) double){0., (double)-23};
    ; do { idres = (d0 > d1); do { int __i; for (__i = 0; __i < 2; __i ++) { if ((idres)[__i] != ((d0)[__i] > (d1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " ">" " " "%f" " ? -1 : 0) ", (idres)[__i], (d0)[__i], (d1)[__i]); __builtin_abort (); } } } while (0); idres = (d0 < d1); do { int __i; for (__i = 0; __i < 2; __i ++) { if ((idres)[__i] != ((d0)[__i] < (d1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " "<" " " "%f" " ? -1 : 0) ", (idres)[__i], (d0)[__i], (d1)[__i]); __builtin_abort (); } } } while (0); idres = (d0 >= d1); do { int __i; for (__i = 0; __i < 2; __i ++) { if ((idres)[__i] != ((d0)[__i] >= (d1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " ">=" " " "%f" " ? -1 : 0) ", (idres)[__i], (d0)[__i], (d1)[__i]); __builtin_abort (); } } } while (0); idres = (d0 <= d1); do { int __i; for (__i = 0; __i < 2; __i ++) { if ((idres)[__i] != ((d0)[__i] <= (d1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " "<=" " " "%f" " ? -1 : 0) ", (idres)[__i], (d0)[__i], (d1)[__i]); __builtin_abort (); } } } while (0); idres = (d0 == d1); do { int __i; for (__i = 0; __i < 2; __i ++) { if ((idres)[__i] != ((d0)[__i] == (d1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " "==" " " "%f" " ? -1 : 0) ", (idres)[__i], (d0)[__i], (d1)[__i]); __builtin_abort (); } } } while (0); idres = (d0 != d1); do { int __i; for (__i = 0; __i < 2; __i ++) { if ((idres)[__i] != ((d0)[__i] != (d1)[__i] ? -1 : 0)) { __builtin_printf ("%i != ((" "%f" " " "!=" " " "%f" " ? -1 : 0) ", (idres)[__i], (d0)[__i], (d1)[__i]); __builtin_abort (); } } } while (0); } while (0);


    return 0;
}
