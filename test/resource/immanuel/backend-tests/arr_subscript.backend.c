0


int main( void )
{
  char *sz;
  sz = "c4";

  if ( sz[0] != 99 ) return 1;
  if ( sz[1] != 52 ) return 2;

  char **psz;
  psz = &sz;

  if ( *(psz[0]) != 99 ) return 3;
  if ( (psz[0])[1] != 52 ) return 4;

  int x;
  x = 5;

  int *p;
  p = &x;
  if ( *p != 5 ) return 5;
  if ( p[0] != 5 ) return 6;

  p[0] = *p + 3;  // 5 + 3
  if ( *p != 8 ) return 7;

  int **pp;
  pp = &p;

  if ( pp[0][0] != 8 ) return 8;
  if ( (*pp)[0] != 8 ) return 9;

  pp[0][0] = 7;
  if ( *p != 7 ) return 10;

  *(pp[0]) = 11;
  if ( x != 11 ) return 11;

  (*pp)[0] = 12;
  if ( x != 12 ) return 12;

  return 0;
}
