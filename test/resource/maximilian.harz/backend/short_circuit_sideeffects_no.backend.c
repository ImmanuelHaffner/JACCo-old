0

int global;

void illuminate();

int main()
{
  if ( 0 || illuminate() )
    return global;
}

void illuminate()
{
  global = 23;
}
