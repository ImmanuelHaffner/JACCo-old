23

int global;

void illuminate();

int main()
{
  if ( 1 || illuminate() )
    return global;
}

void illuminate()
{
  global = 23;
}
