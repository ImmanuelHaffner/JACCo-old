
typedef long unsigned int Size_t;







struct huge_struct
{
  short buf[((1L << (8 * sizeof(Size_t) - 2))-256)];
  int a;
  int b;
  int c;
  int d;
};

union huge_union
{
  int a;
  char buf[((1L << (8 * sizeof(Size_t) - 2))-256)];
};

Size_t union_size()
{
  return sizeof(union huge_union);
}

Size_t struct_size()
{
  return sizeof(struct huge_struct);
}

Size_t struct_a_offset()
{
  return (Size_t)(&((struct huge_struct *) 0)->a);
}

int main()
{

  if (union_size() != sizeof(char) * ((1L << (8 * sizeof(Size_t) - 2))-256))
    abort();

  if (struct_size() != sizeof(short) * ((1L << (8 * sizeof(Size_t) - 2))-256) + 4*sizeof(int))
    abort();

  if (struct_a_offset() < sizeof(short) * ((1L << (8 * sizeof(Size_t) - 2))-256))
    abort();

  return 0;
}
