typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;

void vafunction (char *dummy, ...)
{
  double darg;
  int iarg;
  int flag = 0;
  int i;
  va_list ap;

  __builtin_va_start(ap,dummy);
  for (i = 1; i <= 18; i++, flag++)
    {
      if (flag & 1)
 {
   darg = __builtin_va_arg(ap,double);
   if (darg != (double)i)
     abort();
 }
      else
 {
   iarg = __builtin_va_arg(ap,int);
   if (iarg != i)
     abort();
 }
    }
    __builtin_va_end(ap);
}

int main (void)
{
  vafunction( "",
 1, 2.,
 3, 4.,
 5, 6.,
 7, 8.,
 9, 10.,
 11, 12.,
 13, 14.,
 15, 16.,
 17, 18. );
  exit(0);
  return 0;
}
