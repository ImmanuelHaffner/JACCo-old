struct A { short a, b; int c, d; long e, f; };
typedef struct A TA;
typedef struct A *PA;
typedef TA *PTA;
struct B {};
typedef struct B TB;
typedef struct B *PB;
typedef TB *PTB;
typedef int X[3][3][3];

void
f1 (void *x)
{
  struct A a, *pa1 = &a;
  TA *pa2 = &a;
  PA pa3 = &a;
  PTA pa4 = &a;
  __builtin___memset_chk (&a, 0, sizeof (&a), __builtin_object_size (&a, 1));
  __builtin___memset_chk (pa1, 0, sizeof (pa1), __builtin_object_size (pa1, 1));
  __builtin___memset_chk (pa2, 0, sizeof pa2, __builtin_object_size (pa2, 1));
  __builtin___memset_chk (pa3, 0, sizeof (pa3), __builtin_object_size (pa3, 1));
  __builtin___memset_chk (pa4, 0, sizeof pa4, __builtin_object_size (pa4, 1));
  __builtin___memset_chk (pa1, 0, sizeof (struct A *), __builtin_object_size (pa1, 1));
  __builtin___memset_chk (pa2, 0, sizeof (PTA), __builtin_object_size (pa2, 1));
  __builtin___memset_chk (pa3, 0, sizeof (PA), __builtin_object_size (pa3, 1));
  __builtin___memset_chk (pa4, 0, sizeof (__typeof (pa4)), __builtin_object_size (pa4, 1));

  __builtin___memcpy_chk (&a, x, sizeof (&a), __builtin_object_size (&a, 1));
  __builtin___memcpy_chk (pa1, x, sizeof (pa1), __builtin_object_size (pa1, 1));
  __builtin___memcpy_chk (pa2, x, sizeof pa2, __builtin_object_size (pa2, 1));
  __builtin___memcpy_chk (pa3, x, sizeof (pa3), __builtin_object_size (pa3, 1));
  __builtin___memcpy_chk (pa4, x, sizeof pa4, __builtin_object_size (pa4, 1));
  __builtin___memcpy_chk (pa1, x, sizeof (struct A *), __builtin_object_size (pa1, 1));
  __builtin___memcpy_chk (pa2, x, sizeof (PTA), __builtin_object_size (pa2, 1));
  __builtin___memcpy_chk (pa3, x, sizeof (PA), __builtin_object_size (pa3, 1));
  __builtin___memcpy_chk (pa4, x, sizeof (__typeof (pa4)), __builtin_object_size (pa4, 1));

  __builtin___memcpy_chk (x, &a, sizeof (&a), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa1, sizeof (pa1), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa2, sizeof pa2, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa3, sizeof (pa3), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa4, sizeof pa4, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa1, sizeof (struct A *), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa2, sizeof (PTA), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa3, sizeof (PA), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa4, sizeof (__typeof (pa4)), __builtin_object_size (x, 1));

  __builtin___memmove_chk (&a, x, sizeof (&a), __builtin_object_size (&a, 1));
  __builtin___memmove_chk (pa1, x, sizeof (pa1), __builtin_object_size (pa1, 1));
  __builtin___memmove_chk (pa2, x, sizeof pa2, __builtin_object_size (pa2, 1));
  __builtin___memmove_chk (pa3, x, sizeof (pa3), __builtin_object_size (pa3, 1));
  __builtin___memmove_chk (pa4, x, sizeof pa4, __builtin_object_size (pa4, 1));
  __builtin___memmove_chk (pa1, x, sizeof (struct A *), __builtin_object_size (pa1, 1));
  __builtin___memmove_chk (pa2, x, sizeof (PTA), __builtin_object_size (pa2, 1));
  __builtin___memmove_chk (pa3, x, sizeof (PA), __builtin_object_size (pa3, 1));
  __builtin___memmove_chk (pa4, x, sizeof (__typeof (pa4)), __builtin_object_size (pa4, 1));

  __builtin___memmove_chk (x, &a, sizeof (&a), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa1, sizeof (pa1), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa2, sizeof pa2, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa3, sizeof (pa3), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa4, sizeof pa4, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa1, sizeof (struct A *), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa2, sizeof (PTA), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa3, sizeof (PA), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa4, sizeof (__typeof (pa4)), __builtin_object_size (x, 1));


  __builtin___memset_chk (&a, 0, sizeof a, __builtin_object_size (&a, 1));
  __builtin___memset_chk (&a, 0, sizeof (a), __builtin_object_size (&a, 1));
  __builtin___memset_chk (&a, 0, sizeof (struct A), __builtin_object_size (&a, 1));
  __builtin___memset_chk (&a, 0, sizeof (const struct A), __builtin_object_size (&a, 1));
  __builtin___memset_chk (&a, 0, sizeof (volatile struct A), __builtin_object_size (&a, 1));
  __builtin___memset_chk (&a, 0, sizeof (volatile const struct A), __builtin_object_size (&a, 1));
  __builtin___memset_chk (&a, 0, sizeof (TA), __builtin_object_size (&a, 1));
  __builtin___memset_chk (&a, 0, sizeof (__typeof (*&a)), __builtin_object_size (&a, 1));
  __builtin___memset_chk (pa1, 0, sizeof (*pa1), __builtin_object_size (pa1, 1));
  __builtin___memset_chk (pa2, 0, sizeof (*pa3), __builtin_object_size (pa2, 1));
  __builtin___memset_chk (pa3, 0, sizeof (__typeof (*pa3)), __builtin_object_size (pa3, 1));

  __builtin___memset_chk ((void *) &a, 0, sizeof (&a), __builtin_object_size ((void *) &a, 1));
  __builtin___memset_chk ((char *) &a, 0, sizeof (&a), __builtin_object_size ((char *) &a, 1));
  __builtin___memset_chk (&a, 0, sizeof (&a) + 0, __builtin_object_size (&a, 1));
  __builtin___memset_chk (&a, 0, 0 + sizeof (&a), __builtin_object_size (&a, 1));


  __builtin___memcpy_chk (&a, x, sizeof a, __builtin_object_size (&a, 1));
  __builtin___memcpy_chk (&a, x, sizeof (a), __builtin_object_size (&a, 1));
  __builtin___memcpy_chk (&a, x, sizeof (struct A), __builtin_object_size (&a, 1));
  __builtin___memcpy_chk (&a, x, sizeof (const struct A), __builtin_object_size (&a, 1));
  __builtin___memcpy_chk (&a, x, sizeof (volatile struct A), __builtin_object_size (&a, 1));
  __builtin___memcpy_chk (&a, x, sizeof (volatile const struct A), __builtin_object_size (&a, 1));
  __builtin___memcpy_chk (&a, x, sizeof (TA), __builtin_object_size (&a, 1));
  __builtin___memcpy_chk (&a, x, sizeof (__typeof (*&a)), __builtin_object_size (&a, 1));
  __builtin___memcpy_chk (pa1, x, sizeof (*pa1), __builtin_object_size (pa1, 1));
  __builtin___memcpy_chk (pa2, x, sizeof (*pa3), __builtin_object_size (pa2, 1));
  __builtin___memcpy_chk (pa3, x, sizeof (__typeof (*pa3)), __builtin_object_size (pa3, 1));

  __builtin___memcpy_chk ((void *) &a, x, sizeof (&a), __builtin_object_size ((void *) &a, 1));
  __builtin___memcpy_chk ((char *) &a, x, sizeof (&a), __builtin_object_size ((char *) &a, 1));
  __builtin___memcpy_chk (&a, x, sizeof (&a) + 0, __builtin_object_size (&a, 1));
  __builtin___memcpy_chk (&a, x, 0 + sizeof (&a), __builtin_object_size (&a, 1));


  __builtin___memcpy_chk (x, &a, sizeof a, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &a, sizeof (a), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &a, sizeof (struct A), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &a, sizeof (const struct A), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &a, sizeof (volatile struct A), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &a, sizeof (volatile const struct A), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &a, sizeof (TA), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &a, sizeof (__typeof (*&a)), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa1, sizeof (*pa1), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa2, sizeof (*pa3), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pa3, sizeof (__typeof (*pa3)), __builtin_object_size (x, 1));

  __builtin___memcpy_chk (x, (void *) &a, sizeof (&a), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, (char *) &a, sizeof (&a), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &a, sizeof (&a) + 0, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &a, 0 + sizeof (&a), __builtin_object_size (x, 1));


  __builtin___memmove_chk (&a, x, sizeof a, __builtin_object_size (&a, 1));
  __builtin___memmove_chk (&a, x, sizeof (a), __builtin_object_size (&a, 1));
  __builtin___memmove_chk (&a, x, sizeof (struct A), __builtin_object_size (&a, 1));
  __builtin___memmove_chk (&a, x, sizeof (const struct A), __builtin_object_size (&a, 1));
  __builtin___memmove_chk (&a, x, sizeof (volatile struct A), __builtin_object_size (&a, 1));
  __builtin___memmove_chk (&a, x, sizeof (volatile const struct A), __builtin_object_size (&a, 1));
  __builtin___memmove_chk (&a, x, sizeof (TA), __builtin_object_size (&a, 1));
  __builtin___memmove_chk (&a, x, sizeof (__typeof (*&a)), __builtin_object_size (&a, 1));
  __builtin___memmove_chk (pa1, x, sizeof (*pa1), __builtin_object_size (pa1, 1));
  __builtin___memmove_chk (pa2, x, sizeof (*pa3), __builtin_object_size (pa2, 1));
  __builtin___memmove_chk (pa3, x, sizeof (__typeof (*pa3)), __builtin_object_size (pa3, 1));

  __builtin___memmove_chk ((void *) &a, x, sizeof (&a), __builtin_object_size ((void *) &a, 1));
  __builtin___memmove_chk ((char *) &a, x, sizeof (&a), __builtin_object_size ((char *) &a, 1));
  __builtin___memmove_chk (&a, x, sizeof (&a) + 0, __builtin_object_size (&a, 1));
  __builtin___memmove_chk (&a, x, 0 + sizeof (&a), __builtin_object_size (&a, 1));


  __builtin___memmove_chk (x, &a, sizeof a, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &a, sizeof (a), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &a, sizeof (struct A), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &a, sizeof (const struct A), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &a, sizeof (volatile struct A), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &a, sizeof (volatile const struct A), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &a, sizeof (TA), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &a, sizeof (__typeof (*&a)), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa1, sizeof (*pa1), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa2, sizeof (*pa3), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pa3, sizeof (__typeof (*pa3)), __builtin_object_size (x, 1));

  __builtin___memmove_chk (x, (void *) &a, sizeof (&a), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, (char *) &a, sizeof (&a), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &a, sizeof (&a) + 0, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &a, 0 + sizeof (&a), __builtin_object_size (x, 1));
}

void
f2 (void *x)
{
  struct B b, *pb1 = &b;
  TB *pb2 = &b;
  PB pb3 = &b;
  PTB pb4 = &b;
  __builtin___memset_chk (&b, 0, sizeof (&b), __builtin_object_size (&b, 1));
  __builtin___memset_chk (pb1, 0, sizeof (pb1), __builtin_object_size (pb1, 1));
  __builtin___memset_chk (pb2, 0, sizeof pb2, __builtin_object_size (pb2, 1));
  __builtin___memset_chk (pb3, 0, sizeof (pb3), __builtin_object_size (pb3, 1));
  __builtin___memset_chk (pb4, 0, sizeof pb4, __builtin_object_size (pb4, 1));
  __builtin___memset_chk (pb1, 0, sizeof (struct B *), __builtin_object_size (pb1, 1));
  __builtin___memset_chk (pb2, 0, sizeof (PTB), __builtin_object_size (pb2, 1));
  __builtin___memset_chk (pb3, 0, sizeof (PB), __builtin_object_size (pb3, 1));
  __builtin___memset_chk (pb4, 0, sizeof (__typeof (pb4)), __builtin_object_size (pb4, 1));

  __builtin___memcpy_chk (&b, x, sizeof (&b), __builtin_object_size (&b, 1));
  __builtin___memcpy_chk (pb1, x, sizeof (pb1), __builtin_object_size (pb1, 1));
  __builtin___memcpy_chk (pb2, x, sizeof pb2, __builtin_object_size (pb2, 1));
  __builtin___memcpy_chk (pb3, x, sizeof (pb3), __builtin_object_size (pb3, 1));
  __builtin___memcpy_chk (pb4, x, sizeof pb4, __builtin_object_size (pb4, 1));
  __builtin___memcpy_chk (pb1, x, sizeof (struct B *), __builtin_object_size (pb1, 1));
  __builtin___memcpy_chk (pb2, x, sizeof (PTB), __builtin_object_size (pb2, 1));
  __builtin___memcpy_chk (pb3, x, sizeof (PB), __builtin_object_size (pb3, 1));
  __builtin___memcpy_chk (pb4, x, sizeof (__typeof (pb4)), __builtin_object_size (pb4, 1));

  __builtin___memcpy_chk (x, &b, sizeof (&b), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb1, sizeof (pb1), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb2, sizeof pb2, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb3, sizeof (pb3), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb4, sizeof pb4, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb1, sizeof (struct B *), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb2, sizeof (PTB), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb3, sizeof (PB), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb4, sizeof (__typeof (pb4)), __builtin_object_size (x, 1));

  __builtin___memmove_chk (&b, x, sizeof (&b), __builtin_object_size (&b, 1));
  __builtin___memmove_chk (pb1, x, sizeof (pb1), __builtin_object_size (pb1, 1));
  __builtin___memmove_chk (pb2, x, sizeof pb2, __builtin_object_size (pb2, 1));
  __builtin___memmove_chk (pb3, x, sizeof (pb3), __builtin_object_size (pb3, 1));
  __builtin___memmove_chk (pb4, x, sizeof pb4, __builtin_object_size (pb4, 1));
  __builtin___memmove_chk (pb1, x, sizeof (struct B *), __builtin_object_size (pb1, 1));
  __builtin___memmove_chk (pb2, x, sizeof (PTB), __builtin_object_size (pb2, 1));
  __builtin___memmove_chk (pb3, x, sizeof (PB), __builtin_object_size (pb3, 1));
  __builtin___memmove_chk (pb4, x, sizeof (__typeof (pb4)), __builtin_object_size (pb4, 1));

  __builtin___memmove_chk (x, &b, sizeof (&b), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb1, sizeof (pb1), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb2, sizeof pb2, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb3, sizeof (pb3), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb4, sizeof pb4, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb1, sizeof (struct B *), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb2, sizeof (PTB), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb3, sizeof (PB), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb4, sizeof (__typeof (pb4)), __builtin_object_size (x, 1));


  __builtin___memset_chk (&b, 0, sizeof b, __builtin_object_size (&b, 1));
  __builtin___memset_chk (&b, 0, sizeof (b), __builtin_object_size (&b, 1));
  __builtin___memset_chk (&b, 0, sizeof (struct B), __builtin_object_size (&b, 1));
  __builtin___memset_chk (&b, 0, sizeof (const struct B), __builtin_object_size (&b, 1));
  __builtin___memset_chk (&b, 0, sizeof (volatile struct B), __builtin_object_size (&b, 1));
  __builtin___memset_chk (&b, 0, sizeof (volatile const struct B), __builtin_object_size (&b, 1));
  __builtin___memset_chk (&b, 0, sizeof (TB), __builtin_object_size (&b, 1));
  __builtin___memset_chk (&b, 0, sizeof (__typeof (*&b)), __builtin_object_size (&b, 1));
  __builtin___memset_chk (pb1, 0, sizeof (*pb1), __builtin_object_size (pb1, 1));
  __builtin___memset_chk (pb2, 0, sizeof (*pb3), __builtin_object_size (pb2, 1));
  __builtin___memset_chk (pb3, 0, sizeof (__typeof (*pb3)), __builtin_object_size (pb3, 1));

  __builtin___memset_chk ((void *) &b, 0, sizeof (&b), __builtin_object_size ((void *) &b, 1));
  __builtin___memset_chk ((char *) &b, 0, sizeof (&b), __builtin_object_size ((char *) &b, 1));
  __builtin___memset_chk (&b, 0, sizeof (&b) + 0, __builtin_object_size (&b, 1));
  __builtin___memset_chk (&b, 0, 0 + sizeof (&b), __builtin_object_size (&b, 1));


  __builtin___memcpy_chk (&b, x, sizeof b, __builtin_object_size (&b, 1));
  __builtin___memcpy_chk (&b, x, sizeof (b), __builtin_object_size (&b, 1));
  __builtin___memcpy_chk (&b, x, sizeof (struct B), __builtin_object_size (&b, 1));
  __builtin___memcpy_chk (&b, x, sizeof (const struct B), __builtin_object_size (&b, 1));
  __builtin___memcpy_chk (&b, x, sizeof (volatile struct B), __builtin_object_size (&b, 1));
  __builtin___memcpy_chk (&b, x, sizeof (volatile const struct B), __builtin_object_size (&b, 1));
  __builtin___memcpy_chk (&b, x, sizeof (TB), __builtin_object_size (&b, 1));
  __builtin___memcpy_chk (&b, x, sizeof (__typeof (*&b)), __builtin_object_size (&b, 1));
  __builtin___memcpy_chk (pb1, x, sizeof (*pb1), __builtin_object_size (pb1, 1));
  __builtin___memcpy_chk (pb2, x, sizeof (*pb3), __builtin_object_size (pb2, 1));
  __builtin___memcpy_chk (pb3, x, sizeof (__typeof (*pb3)), __builtin_object_size (pb3, 1));

  __builtin___memcpy_chk ((void *) &b, x, sizeof (&b), __builtin_object_size ((void *) &b, 1));
  __builtin___memcpy_chk ((char *) &b, x, sizeof (&b), __builtin_object_size ((char *) &b, 1));
  __builtin___memcpy_chk (&b, x, sizeof (&b) + 0, __builtin_object_size (&b, 1));
  __builtin___memcpy_chk (&b, x, 0 + sizeof (&b), __builtin_object_size (&b, 1));


  __builtin___memcpy_chk (x, &b, sizeof b, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &b, sizeof (b), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &b, sizeof (struct B), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &b, sizeof (const struct B), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &b, sizeof (volatile struct B), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &b, sizeof (volatile const struct B), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &b, sizeof (TB), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &b, sizeof (__typeof (*&b)), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb1, sizeof (*pb1), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb2, sizeof (*pb3), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, pb3, sizeof (__typeof (*pb3)), __builtin_object_size (x, 1));

  __builtin___memcpy_chk (x, (void *) &b, sizeof (&b), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, (char *) &b, sizeof (&b), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &b, sizeof (&b) + 0, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &b, 0 + sizeof (&b), __builtin_object_size (x, 1));


  __builtin___memmove_chk (&b, x, sizeof b, __builtin_object_size (&b, 1));
  __builtin___memmove_chk (&b, x, sizeof (b), __builtin_object_size (&b, 1));
  __builtin___memmove_chk (&b, x, sizeof (struct B), __builtin_object_size (&b, 1));
  __builtin___memmove_chk (&b, x, sizeof (const struct B), __builtin_object_size (&b, 1));
  __builtin___memmove_chk (&b, x, sizeof (volatile struct B), __builtin_object_size (&b, 1));
  __builtin___memmove_chk (&b, x, sizeof (volatile const struct B), __builtin_object_size (&b, 1));
  __builtin___memmove_chk (&b, x, sizeof (TB), __builtin_object_size (&b, 1));
  __builtin___memmove_chk (&b, x, sizeof (__typeof (*&b)), __builtin_object_size (&b, 1));
  __builtin___memmove_chk (pb1, x, sizeof (*pb1), __builtin_object_size (pb1, 1));
  __builtin___memmove_chk (pb2, x, sizeof (*pb3), __builtin_object_size (pb2, 1));
  __builtin___memmove_chk (pb3, x, sizeof (__typeof (*pb3)), __builtin_object_size (pb3, 1));

  __builtin___memmove_chk ((void *) &b, x, sizeof (&b), __builtin_object_size ((void *) &b, 1));
  __builtin___memmove_chk ((char *) &b, x, sizeof (&b), __builtin_object_size ((char *) &b, 1));
  __builtin___memmove_chk (&b, x, sizeof (&b) + 0, __builtin_object_size (&b, 1));
  __builtin___memmove_chk (&b, x, 0 + sizeof (&b), __builtin_object_size (&b, 1));


  __builtin___memmove_chk (x, &b, sizeof b, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &b, sizeof (b), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &b, sizeof (struct B), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &b, sizeof (const struct B), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &b, sizeof (volatile struct B), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &b, sizeof (volatile const struct B), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &b, sizeof (TB), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &b, sizeof (__typeof (*&b)), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb1, sizeof (*pb1), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb2, sizeof (*pb3), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, pb3, sizeof (__typeof (*pb3)), __builtin_object_size (x, 1));

  __builtin___memmove_chk (x, (void *) &b, sizeof (&b), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, (char *) &b, sizeof (&b), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &b, sizeof (&b) + 0, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &b, 0 + sizeof (&b), __builtin_object_size (x, 1));
}

void
f3 (void *x, char *y, int z, X w)
{
  unsigned char *y1 = (unsigned char *) __builtin_alloca (z + 16);
  char buf1[7];
  signed char buf2[z + 32];
  long buf3[17];
  int *buf4[9];
  signed char *y2 = buf2;
  char c;
  char *y3;
  __builtin___memset_chk (y, 0, sizeof (y), __builtin_object_size (y, 1));
  __builtin___memset_chk (y1, 0, sizeof (y1), __builtin_object_size (y1, 1));
  __builtin___memset_chk (y2, 0, sizeof (y2), __builtin_object_size (y2, 1));
  __builtin___memset_chk (&c, 0, sizeof (&c), __builtin_object_size (&c, 1));
  __builtin___memset_chk (w, 0, sizeof w, __builtin_object_size (w, 1));

  __builtin___memcpy_chk (y, x, sizeof (y), __builtin_object_size (y, 1));
  __builtin___memcpy_chk (y1, x, sizeof (y1), __builtin_object_size (y1, 1));
  __builtin___memcpy_chk (y2, x, sizeof (y2), __builtin_object_size (y2, 1));
  __builtin___memcpy_chk (&c, x, sizeof (&c), __builtin_object_size (&c, 1));
  __builtin___memcpy_chk (w, x, sizeof w, __builtin_object_size (w, 1));

  __builtin___memcpy_chk (x, y, sizeof (y), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, y1, sizeof (y1), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, y2, sizeof (y2), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &c, sizeof (&c), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, w, sizeof w, __builtin_object_size (x, 1));

  __builtin___memmove_chk (y, x, sizeof (y), __builtin_object_size (y, 1));
  __builtin___memmove_chk (y1, x, sizeof (y1), __builtin_object_size (y1, 1));
  __builtin___memmove_chk (y2, x, sizeof (y2), __builtin_object_size (y2, 1));
  __builtin___memmove_chk (&c, x, sizeof (&c), __builtin_object_size (&c, 1));
  __builtin___memmove_chk (w, x, sizeof w, __builtin_object_size (w, 1));

  __builtin___memmove_chk (x, y, sizeof (y), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, y1, sizeof (y1), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, y2, sizeof (y2), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &c, sizeof (&c), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, w, sizeof w, __builtin_object_size (x, 1));


  __builtin___memset_chk (y, 0, sizeof (*y), __builtin_object_size (y, 1));
  __builtin___memset_chk (y1, 0, sizeof (*y2), __builtin_object_size (y1, 1));
  __builtin___memset_chk (buf1, 0, sizeof buf1, __builtin_object_size (buf1, 1));
  __builtin___memset_chk (buf3, 0, sizeof (buf3), __builtin_object_size (buf3, 1));
  __builtin___memset_chk (&buf3[0], 0, sizeof (buf3), __builtin_object_size (&buf3[0], 1));
  __builtin___memset_chk (&buf4[0], 0, sizeof (buf4), __builtin_object_size (&buf4[0], 1));
  __builtin___memset_chk (w, 0, sizeof (X), __builtin_object_size (w, 1));

  __builtin___memset_chk ((void *) y, 0, sizeof (y), __builtin_object_size ((void *) y, 1));
  __builtin___memset_chk ((char *) y1, 0, sizeof (y2), __builtin_object_size ((char *) y1, 1));
  __builtin___memset_chk (y, 0, sizeof (y) + 0, __builtin_object_size (y, 1));
  __builtin___memset_chk (y1, 0, 0 + sizeof (y2), __builtin_object_size (y1, 1));
  __builtin___memset_chk ((void *) &c, 0, sizeof (&c), __builtin_object_size ((void *) &c, 1));
  __builtin___memset_chk ((signed char *) &c, 0, sizeof (&c), __builtin_object_size ((signed char *) &c, 1));
  __builtin___memset_chk (&c, 0, sizeof (&c) + 0, __builtin_object_size (&c, 1));
  __builtin___memset_chk (&c, 0, 0 + sizeof (&c), __builtin_object_size (&c, 1));


  __builtin___memcpy_chk (y, x, sizeof (*y), __builtin_object_size (y, 1));
  __builtin___memcpy_chk (y1, x, sizeof (*y2), __builtin_object_size (y1, 1));
  __builtin___memcpy_chk (buf1, x, sizeof buf1, __builtin_object_size (buf1, 1));
  __builtin___memcpy_chk (buf3, x, sizeof (buf3), __builtin_object_size (buf3, 1));
  __builtin___memcpy_chk (&buf3[0], x, sizeof (buf3), __builtin_object_size (&buf3[0], 1));
  __builtin___memcpy_chk (&buf4[0], x, sizeof (buf4), __builtin_object_size (&buf4[0], 1));
  __builtin___memcpy_chk (&y3, y, sizeof (y3), __builtin_object_size (&y3, 1));
  __builtin___memcpy_chk ((char *) &y3, y, sizeof (y3), __builtin_object_size ((char *) &y3, 1));
  __builtin___memcpy_chk (w, x, sizeof (X), __builtin_object_size (w, 1));

  __builtin___memcpy_chk ((void *) y, x, sizeof (y), __builtin_object_size ((void *) y, 1));
  __builtin___memcpy_chk ((char *) y1, x, sizeof (y2), __builtin_object_size ((char *) y1, 1));
  __builtin___memcpy_chk (y, x, sizeof (y) + 0, __builtin_object_size (y, 1));
  __builtin___memcpy_chk (y1, x, 0 + sizeof (y2), __builtin_object_size (y1, 1));
  __builtin___memcpy_chk ((void *) &c, x, sizeof (&c), __builtin_object_size ((void *) &c, 1));
  __builtin___memcpy_chk ((signed char *) &c, x, sizeof (&c), __builtin_object_size ((signed char *) &c, 1));
  __builtin___memcpy_chk (&c, x, sizeof (&c) + 0, __builtin_object_size (&c, 1));
  __builtin___memcpy_chk (&c, x, 0 + sizeof (&c), __builtin_object_size (&c, 1));


  __builtin___memcpy_chk (x, y, sizeof (*y), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, y1, sizeof (*y2), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, buf1, sizeof buf1, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, buf3, sizeof (buf3), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &buf3[0], sizeof (buf3), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &buf4[0], sizeof (buf4), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (y, &y3, sizeof (y3), __builtin_object_size (y, 1));
  __builtin___memcpy_chk (y, (char *) &y3, sizeof (y3), __builtin_object_size (y, 1));
  __builtin___memcpy_chk (x, w, sizeof (X), __builtin_object_size (x, 1));

  __builtin___memcpy_chk (x, (void *) y, sizeof (y), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, (char *) y1, sizeof (y2), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, y, sizeof (y) + 0, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, y1, 0 + sizeof (y2), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, (void *) &c, sizeof (&c), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, (signed char *) &c, sizeof (&c), __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &c, sizeof (&c) + 0, __builtin_object_size (x, 1));
  __builtin___memcpy_chk (x, &c, 0 + sizeof (&c), __builtin_object_size (x, 1));


  __builtin___memmove_chk (y, x, sizeof (*y), __builtin_object_size (y, 1));
  __builtin___memmove_chk (y1, x, sizeof (*y2), __builtin_object_size (y1, 1));
  __builtin___memmove_chk (buf1, x, sizeof buf1, __builtin_object_size (buf1, 1));
  __builtin___memmove_chk (buf3, x, sizeof (buf3), __builtin_object_size (buf3, 1));
  __builtin___memmove_chk (&buf3[0], x, sizeof (buf3), __builtin_object_size (&buf3[0], 1));
  __builtin___memmove_chk (&buf4[0], x, sizeof (buf4), __builtin_object_size (&buf4[0], 1));
  __builtin___memmove_chk (&y3, y, sizeof (y3), __builtin_object_size (&y3, 1));
  __builtin___memmove_chk ((char *) &y3, y, sizeof (y3), __builtin_object_size ((char *) &y3, 1));
  __builtin___memmove_chk (w, x, sizeof (X), __builtin_object_size (w, 1));

  __builtin___memmove_chk ((void *) y, x, sizeof (y), __builtin_object_size ((void *) y, 1));
  __builtin___memmove_chk ((char *) y1, x, sizeof (y2), __builtin_object_size ((char *) y1, 1));
  __builtin___memmove_chk (y, x, sizeof (y) + 0, __builtin_object_size (y, 1));
  __builtin___memmove_chk (y1, x, 0 + sizeof (y2), __builtin_object_size (y1, 1));
  __builtin___memmove_chk ((void *) &c, x, sizeof (&c), __builtin_object_size ((void *) &c, 1));
  __builtin___memmove_chk ((signed char *) &c, x, sizeof (&c), __builtin_object_size ((signed char *) &c, 1));
  __builtin___memmove_chk (&c, x, sizeof (&c) + 0, __builtin_object_size (&c, 1));
  __builtin___memmove_chk (&c, x, 0 + sizeof (&c), __builtin_object_size (&c, 1));


  __builtin___memmove_chk (x, y, sizeof (*y), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, y1, sizeof (*y2), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, buf1, sizeof buf1, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, buf3, sizeof (buf3), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &buf3[0], sizeof (buf3), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &buf4[0], sizeof (buf4), __builtin_object_size (x, 1));
  __builtin___memmove_chk (y, &y3, sizeof (y3), __builtin_object_size (y, 1));
  __builtin___memmove_chk (y, (char *) &y3, sizeof (y3), __builtin_object_size (y, 1));
  __builtin___memmove_chk (x, w, sizeof (X), __builtin_object_size (x, 1));

  __builtin___memmove_chk (x, (void *) y, sizeof (y), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, (char *) y1, sizeof (y2), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, y, sizeof (y) + 0, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, y1, 0 + sizeof (y2), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, (void *) &c, sizeof (&c), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, (signed char *) &c, sizeof (&c), __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &c, sizeof (&c) + 0, __builtin_object_size (x, 1));
  __builtin___memmove_chk (x, &c, 0 + sizeof (&c), __builtin_object_size (x, 1));
}

void
f4 (char *x, char **y, int z, char w[64])
{
  const char *s1 = "foobarbaz";
  const char *s2 = "abcde12345678";
  __builtin___strncpy_chk (x, s1, sizeof (s1), __builtin_object_size (x, 1));
  __builtin___strncat_chk (x, s2, sizeof (s2), __builtin_object_size (x, 1));
  __builtin___stpncpy_chk (x, s1, sizeof (s1), __builtin_object_size (x, 1));

  __builtin___strncpy_chk (w, s1, sizeof (w), __builtin_object_size (w, 1));
  __builtin___strncat_chk (w, s2, sizeof (w), __builtin_object_size (w, 1));
  __builtin___stpncpy_chk (w, s1, sizeof (w), __builtin_object_size (w, 1));


  const char s3[] = "foobarbaz";
  const char s4[] = "abcde12345678";
  __builtin___strncpy_chk (x, s3, sizeof (s3), __builtin_object_size (x, 1));
  __builtin___strncat_chk (x, s4, sizeof (s4), __builtin_object_size (x, 1));
  __builtin___stpncpy_chk (x, s3, sizeof (s3), __builtin_object_size (x, 1));
}
