



typedef long unsigned int size_t;



extern int snprintf (char *, size_t, const char *, ...);
extern int vsnprintf (char *, size_t, const char *, __builtin_va_list);
extern void *memchr (const void *, int, size_t);




struct A { short a, b; int c, d; long e, f; };
typedef struct A TA;
typedef struct A *PA;
typedef TA *PTA;
struct B {};
typedef struct B TB;
typedef struct B *PB;
typedef TB *PTB;
typedef int X[3][3][3];

void foo (void **);

void
f1 (void *x)
{
  struct A a, *pa1 = &a;
  TA *pa2 = &a;
  PA pa3 = &a;
  PTA pa4 = &a;
  void *arr[100];
  int i = 0;
  arr[i++] = memchr (&a, 0, sizeof (&a));
  arr[i++] = memchr (pa1, 0, sizeof (pa1));
  arr[i++] = memchr (pa2, 0, sizeof pa2);
  arr[i++] = memchr (pa3, 0, sizeof (pa3));
  arr[i++] = memchr (pa4, 0, sizeof pa4);
  arr[i++] = memchr (pa1, 0, sizeof (struct A *));
  arr[i++] = memchr (pa2, 0, sizeof (PTA));
  arr[i++] = memchr (pa3, 0, sizeof (PA));
  arr[i++] = memchr (pa4, 0, sizeof (__typeof (pa4)));


  arr[i++] = memchr (&a, 0, sizeof a);
  arr[i++] = memchr (&a, 0, sizeof (a));
  arr[i++] = memchr (&a, 0, sizeof (struct A));
  arr[i++] = memchr (&a, 0, sizeof (const struct A));
  arr[i++] = memchr (&a, 0, sizeof (volatile struct A));
  arr[i++] = memchr (&a, 0, sizeof (volatile const struct A));
  arr[i++] = memchr (&a, 0, sizeof (TA));
  arr[i++] = memchr (&a, 0, sizeof (__typeof (*&a)));
  arr[i++] = memchr (pa1, 0, sizeof (*pa1));
  arr[i++] = memchr (pa2, 0, sizeof (*pa3));
  arr[i++] = memchr (pa3, 0, sizeof (__typeof (*pa3)));

  arr[i++] = memchr ((void *) &a, 0, sizeof (&a));
  arr[i++] = memchr ((char *) &a, 0, sizeof (&a));
  arr[i++] = memchr (&a, 0, sizeof (&a) + 0);
  arr[i++] = memchr (&a, 0, 0 + sizeof (&a));

  foo (arr);
}

void
f2 (void *x)
{
  struct B b, *pb1 = &b;
  TB *pb2 = &b;
  PB pb3 = &b;
  PTB pb4 = &b;
  void *arr[100];
  int i = 0;
  arr[i++] = memchr (&b, 0, sizeof (&b));
  arr[i++] = memchr (pb1, 0, sizeof (pb1));
  arr[i++] = memchr (pb2, 0, sizeof pb2);
  arr[i++] = memchr (pb3, 0, sizeof (pb3));
  arr[i++] = memchr (pb4, 0, sizeof pb4);
  arr[i++] = memchr (pb1, 0, sizeof (struct B *));
  arr[i++] = memchr (pb2, 0, sizeof (PTB));
  arr[i++] = memchr (pb3, 0, sizeof (PB));
  arr[i++] = memchr (pb4, 0, sizeof (__typeof (pb4)));


  arr[i++] = memchr (&b, 0, sizeof b);
  arr[i++] = memchr (&b, 0, sizeof (b));
  arr[i++] = memchr (&b, 0, sizeof (struct B));
  arr[i++] = memchr (&b, 0, sizeof (const struct B));
  arr[i++] = memchr (&b, 0, sizeof (volatile struct B));
  arr[i++] = memchr (&b, 0, sizeof (volatile const struct B));
  arr[i++] = memchr (&b, 0, sizeof (TB));
  arr[i++] = memchr (&b, 0, sizeof (__typeof (*&b)));
  arr[i++] = memchr (pb1, 0, sizeof (*pb1));
  arr[i++] = memchr (pb2, 0, sizeof (*pb3));
  arr[i++] = memchr (pb3, 0, sizeof (__typeof (*pb3)));

  arr[i++] = memchr ((void *) &b, 0, sizeof (&b));
  arr[i++] = memchr ((char *) &b, 0, sizeof (&b));
  arr[i++] = memchr (&b, 0, sizeof (&b) + 0);
  arr[i++] = memchr (&b, 0, 0 + sizeof (&b));

  foo (arr);
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
  void *arr[100];
  int i = 0;
  arr[i++] = memchr (y, 0, sizeof (y));
  arr[i++] = memchr (y1, 0, sizeof (y1));
  arr[i++] = memchr (y2, 0, sizeof (y2));
  arr[i++] = memchr (&c, 0, sizeof (&c));
  arr[i++] = memchr (w, 0, sizeof w);


  arr[i++] = memchr (y, 0, sizeof (*y));
  arr[i++] = memchr (y1, 0, sizeof (*y2));
  arr[i++] = memchr (buf1, 0, sizeof buf1);
  arr[i++] = memchr (buf3, 0, sizeof (buf3));
  arr[i++] = memchr (&buf3[0], 0, sizeof (buf3));
  arr[i++] = memchr (&buf4[0], 0, sizeof (buf4));
  arr[i++] = memchr (w, 0, sizeof (X));

  arr[i++] = memchr ((void *) y, 0, sizeof (y));
  arr[i++] = memchr ((char *) y1, 0, sizeof (y2));
  arr[i++] = memchr (y, 0, sizeof (y) + 0);
  arr[i++] = memchr (y1, 0, 0 + sizeof (y2));
  arr[i++] = memchr ((void *) &c, 0, sizeof (&c));
  arr[i++] = memchr ((signed char *) &c, 0, sizeof (&c));
  arr[i++] = memchr (&c, 0, sizeof (&c) + 0);
  arr[i++] = memchr (&c, 0, 0 + sizeof (&c));

  foo (arr);
}

void
f4 (char x[64], char *y, __builtin_va_list ap)
{
  char buf[128], *p = buf;
  snprintf (x, sizeof (x), "%s", y);
  vsnprintf (x, sizeof (x), "%s", ap);
  snprintf (p, sizeof (p), "%s", y);
  vsnprintf (p, sizeof (p), "%s", ap);


  snprintf (buf, sizeof (buf), "%s", y);
  vsnprintf (buf, sizeof (buf), "%s", ap);
  snprintf (p, sizeof (buf), "%s", y);
  vsnprintf (p, sizeof (buf), "%s", ap);
}
