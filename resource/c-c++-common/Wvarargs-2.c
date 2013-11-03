




typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;

void
err (int a)
{
  va_list vp;
  __builtin_va_start(vp,a);
}

void
foo0 (int a, int b, ...)
{
    va_list vp;


    __builtin_va_start(vp,a);
    __builtin_va_end(vp);
}

void
foo1 (int a, register int b, ...)
{
    va_list vp;


    __builtin_va_start(vp,b);
    __builtin_va_end(vp);
}
