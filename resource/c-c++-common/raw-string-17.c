const char x[] = R"(
abc
)";
const char y[] = R"( abc

 ");
const char z[] = "\nabc\n";
const char w[] = R"( abc "\n"
    ");

int
main ()
{
  if (sizeof x != sizeof y
      || sizeof x != sizeof z
      || sizeof x != sizeof w
      || __builtin_memcmp (x, y, sizeof x)
      || __builtin_memcmp (x, z, sizeof x)
      || __builtin_memcmp (x, w, sizeof x))
    __builtin_abort ();
  return 0;
}
