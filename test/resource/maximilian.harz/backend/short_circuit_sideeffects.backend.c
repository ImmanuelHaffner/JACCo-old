23


int global;

int illuminate();

int main()
{
  global = 0;
  if ( 0 || illuminate() )
    return global;
}

int illuminate()
{
  global = 23;
  return 1;
}
