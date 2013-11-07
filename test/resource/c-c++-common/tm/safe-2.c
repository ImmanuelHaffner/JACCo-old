


void mco(void) __attribute__((transaction_may_cancel_outer));

void
f(void)
{
  mco();
  __transaction_atomic {
    mco();
  }
  __transaction_relaxed {
    mco();
  }
  __transaction_atomic [[outer]] {
    mco();
  }
  __transaction_atomic [[outer]] {
    __transaction_atomic {
      __transaction_atomic {
 __transaction_atomic {
   mco();
 }
      }
    }
  }
}

void __attribute__((transaction_may_cancel_outer))
g(void)
{
  mco();
  __transaction_atomic {
    __transaction_atomic {
      __transaction_atomic {
 __transaction_atomic {
   mco();
 }
      }
    }
  }
}
