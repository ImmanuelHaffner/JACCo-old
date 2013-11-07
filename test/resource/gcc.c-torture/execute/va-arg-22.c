typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;

extern void abort (void);
extern void exit (int);

void bar (int n, int c)
{
  static int lastn = -1, lastc = -1;

  if (lastn != n)
    {
      if (lastc != lastn)
 abort ();
      lastc = 0;
      lastn = n;
    }

  if (c != (char) (lastc ^ (n << 3)))
    abort ();
  lastc++;
}


typedef struct { char x[0]; } A0; typedef struct { char x[1]; } A1; typedef struct { char x[2]; } A2; typedef struct { char x[3]; } A3; typedef struct { char x[4]; } A4; typedef struct { char x[5]; } A5; typedef struct { char x[6]; } A6; typedef struct { char x[7]; } A7;
typedef struct { char x[8]; } A8; typedef struct { char x[9]; } A9; typedef struct { char x[10]; } A10; typedef struct { char x[11]; } A11; typedef struct { char x[12]; } A12; typedef struct { char x[13]; } A13; typedef struct { char x[14]; } A14; typedef struct { char x[15]; } A15;
typedef struct { char x[16]; } A16; typedef struct { char x[31]; } A31; typedef struct { char x[32]; } A32; typedef struct { char x[35]; } A35; typedef struct { char x[72]; } A72;


void foo (int size, ...)
{

A0 a0; A1 a1; A2 a2; A3 a3; A4 a4; A5 a5; A6 a6; A7 a7;
A8 a8; A9 a9; A10 a10; A11 a11; A12 a12; A13 a13; A14 a14; A15 a15;
A16 a16; A31 a31; A32 a32; A35 a35; A72 a72;

  va_list ap;
  int i;

  if (size != 21)
    abort ();
  __builtin_va_start(ap,size);




a0 = __builtin_va_arg(ap,typeof (a0)); for (i = 0; i < 0; i++) bar (0, a0.x[i]); a1 = __builtin_va_arg(ap,typeof (a1)); for (i = 0; i < 1; i++) bar (1, a1.x[i]); a2 = __builtin_va_arg(ap,typeof (a2)); for (i = 0; i < 2; i++) bar (2, a2.x[i]); a3 = __builtin_va_arg(ap,typeof (a3)); for (i = 0; i < 3; i++) bar (3, a3.x[i]); a4 = __builtin_va_arg(ap,typeof (a4)); for (i = 0; i < 4; i++) bar (4, a4.x[i]); a5 = __builtin_va_arg(ap,typeof (a5)); for (i = 0; i < 5; i++) bar (5, a5.x[i]); a6 = __builtin_va_arg(ap,typeof (a6)); for (i = 0; i < 6; i++) bar (6, a6.x[i]); a7 = __builtin_va_arg(ap,typeof (a7)); for (i = 0; i < 7; i++) bar (7, a7.x[i]);
a8 = __builtin_va_arg(ap,typeof (a8)); for (i = 0; i < 8; i++) bar (8, a8.x[i]); a9 = __builtin_va_arg(ap,typeof (a9)); for (i = 0; i < 9; i++) bar (9, a9.x[i]); a10 = __builtin_va_arg(ap,typeof (a10)); for (i = 0; i < 10; i++) bar (10, a10.x[i]); a11 = __builtin_va_arg(ap,typeof (a11)); for (i = 0; i < 11; i++) bar (11, a11.x[i]); a12 = __builtin_va_arg(ap,typeof (a12)); for (i = 0; i < 12; i++) bar (12, a12.x[i]); a13 = __builtin_va_arg(ap,typeof (a13)); for (i = 0; i < 13; i++) bar (13, a13.x[i]); a14 = __builtin_va_arg(ap,typeof (a14)); for (i = 0; i < 14; i++) bar (14, a14.x[i]); a15 = __builtin_va_arg(ap,typeof (a15)); for (i = 0; i < 15; i++) bar (15, a15.x[i]);
a16 = __builtin_va_arg(ap,typeof (a16)); for (i = 0; i < 16; i++) bar (16, a16.x[i]); a31 = __builtin_va_arg(ap,typeof (a31)); for (i = 0; i < 31; i++) bar (31, a31.x[i]); a32 = __builtin_va_arg(ap,typeof (a32)); for (i = 0; i < 32; i++) bar (32, a32.x[i]); a35 = __builtin_va_arg(ap,typeof (a35)); for (i = 0; i < 35; i++) bar (35, a35.x[i]); a72 = __builtin_va_arg(ap,typeof (a72)); for (i = 0; i < 72; i++) bar (72, a72.x[i]);

  __builtin_va_end(ap);
}

int main (void)
{

A0 a0; A1 a1; A2 a2; A3 a3; A4 a4; A5 a5; A6 a6; A7 a7;
A8 a8; A9 a9; A10 a10; A11 a11; A12 a12; A13 a13; A14 a14; A15 a15;
A16 a16; A31 a31; A32 a32; A35 a35; A72 a72;

  int i;




for (i = 0; i < 0; i++) a0.x[i] = i ^ (0 << 3); for (i = 0; i < 1; i++) a1.x[i] = i ^ (1 << 3); for (i = 0; i < 2; i++) a2.x[i] = i ^ (2 << 3); for (i = 0; i < 3; i++) a3.x[i] = i ^ (3 << 3); for (i = 0; i < 4; i++) a4.x[i] = i ^ (4 << 3); for (i = 0; i < 5; i++) a5.x[i] = i ^ (5 << 3); for (i = 0; i < 6; i++) a6.x[i] = i ^ (6 << 3); for (i = 0; i < 7; i++) a7.x[i] = i ^ (7 << 3);
for (i = 0; i < 8; i++) a8.x[i] = i ^ (8 << 3); for (i = 0; i < 9; i++) a9.x[i] = i ^ (9 << 3); for (i = 0; i < 10; i++) a10.x[i] = i ^ (10 << 3); for (i = 0; i < 11; i++) a11.x[i] = i ^ (11 << 3); for (i = 0; i < 12; i++) a12.x[i] = i ^ (12 << 3); for (i = 0; i < 13; i++) a13.x[i] = i ^ (13 << 3); for (i = 0; i < 14; i++) a14.x[i] = i ^ (14 << 3); for (i = 0; i < 15; i++) a15.x[i] = i ^ (15 << 3);
for (i = 0; i < 16; i++) a16.x[i] = i ^ (16 << 3); for (i = 0; i < 31; i++) a31.x[i] = i ^ (31 << 3); for (i = 0; i < 32; i++) a32.x[i] = i ^ (32 << 3); for (i = 0; i < 35; i++) a35.x[i] = i ^ (35 << 3); for (i = 0; i < 72; i++) a72.x[i] = i ^ (72 << 3);


  foo (21

, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7
, a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15
, a16 , a31 , a32 , a35 , a72

      );
  exit (0);
}
