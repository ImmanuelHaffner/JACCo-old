



int main()
{
  __complex double dc;
  double *dp = &(__real dc);
  *dp = 3.14;
  if ((__real dc) != 3.14) abort();
  exit (0);
}
