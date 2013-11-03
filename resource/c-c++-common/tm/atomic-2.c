


int g;
void f(void)
{
  __transaction_atomic {
    g++;
  }
}
