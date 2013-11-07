typedef long int ptrdiff_t;
typedef long unsigned int size_t;
typedef int wchar_t;

const wchar_t ws[] = L"foo";

int
main (void)
{
  if (ws[0] != L'f' || ws[1] != L'o' || ws[2] != L'o' || ws[3] != L'\0')
    abort();
  exit(0);
}
