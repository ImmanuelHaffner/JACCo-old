




int __attribute__((naked))
foo(void)
{
  __asm__ ("");
}

int __attribute__((naked,noreturn))
bar(void)
{
  __asm__ ("");
}
