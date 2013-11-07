

void f(void)
{
  __transaction_atomic {
    __transaction_cancel;
  }
}
