


extern int a[][10], a2[][10];
int b[10], c[10][2], d[10], e[10], f[10];
int b2[10], c2[10][2], d2[10], e2[10], f2[10];
int k[10], l[10], m[10], n[10], o;
int *p;
int **q;
int r[4][4][4][4][4];
int t[10];
void bar (int *);

void
foo (int g[3][10], int h[4][8], int i[2][10], int j[][9],
     int g2[3][10], int h2[4][8], int i2[2][10], int j2[][9])
{
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    bar (&a[0][0]);
    bar (b);
    bar (&c[0][0]);
    bar (d);
    bar (e);
    bar (f);
    bar (&g[0][0]);
    bar (&h[0][0]);
    bar (&h[0][0]);
    bar (&i[0][0]);
    bar (&j[0][0]);
    bar (&j[0][0]);
    bar (&a2[0][0]);
    bar (&a2[0][0]);
    bar (&a2[0][0]);
    bar (b2);
    bar (&c2[0][0]);
    bar (d2);
    bar (e2);
    bar (f2);
    bar (&g2[0][0]);
    bar (&h2[0][0]);
    bar (&h2[0][0]);
    bar (&i2[0][0]);
    bar (&j2[0][0]);
    bar (&j2[0][0]);
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
}
