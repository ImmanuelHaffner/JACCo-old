



int x[2] = { 1, 2 };
void
foo (void)
{
  asm volatile ("" :: "s" (x), "i" (x));


  asm volatile ("" :: "s" ("string"), "i" ("string"));
  asm volatile ("" :: "s" ("raw/gcc.c-torture/compile/pr27528.c"), "i" ("raw/gcc.c-torture/compile/pr27528.c"));
  asm volatile ("" :: "s" (__FUNCTION__), "i" (__FUNCTION__));
}
