int glob0, glob1;



reg0reg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{r0 = r1; }

reg0indreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{r0 = (*p1); }

reg0imm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{r0 = 33; }

reg0limm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{r0 = ((float)(int)&glob1); }

reg0adr1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{r0 = (*((float *)(11111111 & ~(__alignof__ (float) - 1)))); }

reg0adrreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{r0 = (p1[1111111/4]); }

reg0adrx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{r0 = (((float *)(11111111 & ~(__alignof__ (float) - 1)))[x1]); }

reg0regx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{r0 = (p1[x1]); }

indreg0reg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*p0) = r1; }

indreg0indreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*p0) = (*p1); }

indreg0imm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*p0) = 33; }

indreg0limm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*p0) = ((float)(int)&glob1); }

indreg0adr1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*p0) = (*((float *)(11111111 & ~(__alignof__ (float) - 1)))); }

indreg0adrreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*p0) = (p1[1111111/4]); }

indreg0adrx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*p0) = (((float *)(11111111 & ~(__alignof__ (float) - 1)))[x1]); }

indreg0regx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*p0) = (p1[x1]); }

adr0reg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*((float *)10000000)) = r1; }

adr0indreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*((float *)10000000)) = (*p1); }

adr0imm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*((float *)10000000)) = 33; }

adr0limm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*((float *)10000000)) = ((float)(int)&glob1); }

adr0adr1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*((float *)10000000)) = (*((float *)(11111111 & ~(__alignof__ (float) - 1)))); }

adr0adrreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*((float *)10000000)) = (p1[1111111/4]); }

adr0adrx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*((float *)10000000)) = (((float *)(11111111 & ~(__alignof__ (float) - 1)))[x1]); }

adr0regx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(*((float *)10000000)) = (p1[x1]); }

adrreg0reg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[10000000]) = r1; }

adrreg0indreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[10000000]) = (*p1); }

adrreg0imm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[10000000]) = 33; }

adrreg0limm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[10000000]) = ((float)(int)&glob1); }

adrreg0adr1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[10000000]) = (*((float *)(11111111 & ~(__alignof__ (float) - 1)))); }

adrreg0adrreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[10000000]) = (p1[1111111/4]); }

adrreg0adrx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[10000000]) = (((float *)(11111111 & ~(__alignof__ (float) - 1)))[x1]); }

adrreg0regx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[10000000]) = (p1[x1]); }

adrx0reg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(((float *)10000000)[x0]) = r1; }

adrx0indreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(((float *)10000000)[x0]) = (*p1); }

adrx0imm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(((float *)10000000)[x0]) = 33; }

adrx0limm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(((float *)10000000)[x0]) = ((float)(int)&glob1); }

adrx0adr1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(((float *)10000000)[x0]) = (*((float *)(11111111 & ~(__alignof__ (float) - 1)))); }

adrx0adrreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(((float *)10000000)[x0]) = (p1[1111111/4]); }

adrx0adrx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(((float *)10000000)[x0]) = (((float *)(11111111 & ~(__alignof__ (float) - 1)))[x1]); }

adrx0regx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(((float *)10000000)[x0]) = (p1[x1]); }

regx0reg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[x0]) = r1; }

regx0indreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[x0]) = (*p1); }

regx0imm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[x0]) = 33; }

regx0limm1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[x0]) = ((float)(int)&glob1); }

regx0adr1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[x0]) = (*((float *)(11111111 & ~(__alignof__ (float) - 1)))); }

regx0adrreg1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[x0]) = (p1[1111111/4]); }

regx0adrx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[x0]) = (((float *)(11111111 & ~(__alignof__ (float) - 1)))[x1]); }

regx0regx1_set (r0, r1, x0, x1, p0, p1)
float r0, r1; float *p0, *p1;
{(p0[x0]) = (p1[x1]); }
