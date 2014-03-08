1
a a a a

int main(int argc, char **argv)
{
  char **x;
  x = argv;

  ++x;
  if ( x != argv + 1 ) return 11;

  x--;
  if ( x != argv +1 -1 ) return 12;

  x++;
  if ( x != argv + 1 ) return 13;

  --x;
  if ( x != argv ) return 14;

  ++(++x);
  if ( x != argv + 2 ) return 15;

  x = x--;
  if ( x != argv + 2 ) return 16;

  x = ++(--x);
  if ( x != argv + 2 ) return 17;

  (x--)--;
  /* x == argv */

  return x == argv;
}
