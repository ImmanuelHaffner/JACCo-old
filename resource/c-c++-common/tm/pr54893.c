




volatile int test_var = 0;

int main()
{
  __transaction_relaxed {
    test_var++;
  }
}
