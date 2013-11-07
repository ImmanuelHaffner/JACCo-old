





extern int init (void);

int
fun(void)
{
  static int memo;
  return (memo ?: (memo = init()));
}
