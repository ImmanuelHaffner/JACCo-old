0


int main(void)
{
  char c;
  int i;

  c = 256;
  if ( c != 0 ) return 1;

  c = -1; // 255
  i = c;
  if ( i != 255 ) return 2;

  i = 256;
  c = i;
  if ( c != 0 ) return 3;

  /* test casting an i1 value */
  c = ( 4 == 5 );
  if ( c != 0 ) return 4;

  i = ( 4 == 4 );
  if ( i != 1 ) return 5;

  return 0;
}
