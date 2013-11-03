




struct _IO_FILE {
  int _flags;
};

typedef struct _IO_FILE __FILE;
typedef struct _IO_FILE _IO_FILE;
typedef long int wchar_t;

extern wchar_t *fgetws (wchar_t *__restrict __ws, int __n,
                        __FILE *__restrict __stream);

wchar_t *
fgetws (buf, n, fp)
     wchar_t *buf;
     int n;
     _IO_FILE *fp;
{
  return (wchar_t *)0;
}
