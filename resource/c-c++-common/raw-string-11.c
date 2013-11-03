




int main ()
{
  return __builtin_memcmp (R"raw(foo%sbar%sfred%sbob?????)raw",
      "foo%sbar%sfred%sbob?""?""?""?""?",
      sizeof ("foo%sbar%sfred%sbob?""?""?""?""?"));
}
