0


int main(void)
{
  int x;
  x = 0;

  ++x;
  if ( x != 1 ) return 11;

  x--;
  if ( x != 0 ) return 12;

  x++;
  if ( x != 1 ) return 13;

  --x;
  if ( x != 0 ) return 14;

  ++(++x);
  if ( x != 2 ) return 15;

  x = x--;
  if ( x != 2 ) return 16;

  x = ++(--x);
  if ( x != 2 ) return 17;

  (x--)--;
  /* x == 0 */

  return x;
}
