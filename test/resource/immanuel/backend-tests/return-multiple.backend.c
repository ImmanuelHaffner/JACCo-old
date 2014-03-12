127


int main(int argc, char **argv)
{
  if ( argc > 3 )
    return 1;
  else if ( argc == 3 )
    return 2;

  if ( argc == 0 )
    return 3;
  else
    return 127;
}
