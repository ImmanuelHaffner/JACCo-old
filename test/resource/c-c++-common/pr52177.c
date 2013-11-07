



int *s;

static inline int
foo ()
{
  return sizeof (int);
}

int
bar ()
{
  return __atomic_always_lock_free (foo (), s);
}

int
baz ()
{
  return __atomic_is_lock_free (foo (), s);
}
