

typedef long unsigned int size_t;

extern void abort(void);
extern int memcmp(const void *, const void *, size_t);

double n1 = __builtin_nan("0x1");
double n2 = __builtin_nan("0X1");

int main()
{
  if (memcmp (&n1, &n2, sizeof(double)))
    abort();
  return 0;
}
