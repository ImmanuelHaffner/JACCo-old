


void orig(void);
void xyzzy(void) __attribute__((transaction_wrap (orig)));

void foo() { __transaction_relaxed { orig (); } }
