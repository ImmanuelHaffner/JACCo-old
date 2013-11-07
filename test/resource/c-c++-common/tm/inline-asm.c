


static inline void
inline_death ()
{
  __asm__ ("");
}

void
tranfunction ()
{
  __transaction_atomic
    {
      inline_death ();
    }
}
