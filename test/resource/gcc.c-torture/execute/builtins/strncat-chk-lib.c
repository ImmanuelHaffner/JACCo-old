typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;













typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef long int __swblk_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;

typedef long int __ssize_t;



typedef __off64_t __loff_t;
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;



typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;




typedef __loff_t loff_t;



typedef __ino_t ino_t;
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
typedef __pid_t pid_t;





typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;


typedef __clock_t clock_t;





typedef __time_t time_t;



typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef long unsigned int size_t;



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef int int8_t __attribute__ ((__mode__ (__QI__)));
typedef int int16_t __attribute__ ((__mode__ (__HI__)));
typedef int int32_t __attribute__ ((__mode__ (__SI__)));
typedef int int64_t __attribute__ ((__mode__ (__DI__)));


typedef unsigned int u_int8_t __attribute__ ((__mode__ (__QI__)));
typedef unsigned int u_int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int u_int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int u_int64_t __attribute__ ((__mode__ (__DI__)));

typedef int register_t __attribute__ ((__mode__ (__word__)));




typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;



typedef __sigset_t sigset_t;





struct timespec
  {
    __time_t tv_sec;
    long int tv_nsec;
  };

struct timeval
  {
    __time_t tv_sec;
    __suseconds_t tv_usec;
  };


typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;

extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);





__extension__
extern unsigned int gnu_dev_major (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned int gnu_dev_minor (unsigned long long int __dev)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__
extern unsigned long long int gnu_dev_makedev (unsigned int __major,
            unsigned int __minor)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));






typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
typedef unsigned long int pthread_t;


typedef union
{
  char __size[56];
  long int __align;
} pthread_attr_t;



typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;

    unsigned int __nusers;



    int __kind;

    int __spins;
    __pthread_list_t __list;
  } __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;





typedef union
{

  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;


    unsigned int __flags;
  } __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;





extern void abort (void);

extern int inside_main;
void *chk_fail_buf[256] __attribute__((aligned (16)));
volatile int chk_fail_allowed, chk_calls;
volatile int memcpy_disallowed, mempcpy_disallowed, memmove_disallowed;
volatile int memset_disallowed, strcpy_disallowed, stpcpy_disallowed;
volatile int strncpy_disallowed, stpncpy_disallowed, strcat_disallowed;
volatile int strncat_disallowed, sprintf_disallowed, vsprintf_disallowed;
volatile int snprintf_disallowed, vsnprintf_disallowed;
extern long unsigned int strlen (const char *);
extern int vsprintf (char *, const char *, va_list);

void __attribute__((noreturn))
__chk_fail (void)
{
  if (chk_fail_allowed)
    __builtin_longjmp (chk_fail_buf, 1);
  abort ();
}

void *
memcpy (void *dst, const void *src, long unsigned int n)
{
  const char *srcp;
  char *dstp;






  srcp = src;
  dstp = dst;
  while (n-- != 0)
    *dstp++ = *srcp++;

  return dst;
}

void *
__memcpy_chk (void *dst, const void *src, long unsigned int n, long unsigned int size)
{

  if (size == (long unsigned int) -1)
    abort ();
  ++chk_calls;
  if (n > size)
    __chk_fail ();
  return memcpy (dst, src, n);
}

void *
mempcpy (void *dst, const void *src, long unsigned int n)
{
  const char *srcp;
  char *dstp;






  srcp = src;
  dstp = dst;
  while (n-- != 0)
    *dstp++ = *srcp++;

  return dstp;
}

void *
__mempcpy_chk (void *dst, const void *src, long unsigned int n, long unsigned int size)
{

  if (size == (long unsigned int) -1)
    abort ();
  ++chk_calls;
  if (n > size)
    __chk_fail ();
  return mempcpy (dst, src, n);
}

void *
memmove (void *dst, const void *src, long unsigned int n)
{
  const char *srcp;
  char *dstp;






  srcp = src;
  dstp = dst;
  if (srcp < dstp)
    while (n-- != 0)
      dstp[n] = srcp[n];
  else
    while (n-- != 0)
      *dstp++ = *srcp++;

  return dst;
}

void *
__memmove_chk (void *dst, const void *src, long unsigned int n, long unsigned int size)
{

  if (size == (long unsigned int) -1)
    abort ();
  ++chk_calls;
  if (n > size)
    __chk_fail ();
  return memmove (dst, src, n);
}

void *
memset (void *dst, int c, long unsigned int n)
{







  while (n-- != 0)
    n[(char *) dst] = c;

  return dst;
}

void *
__memset_chk (void *dst, int c, long unsigned int n, long unsigned int size)
{

  if (size == (long unsigned int) -1)
    abort ();
  ++chk_calls;
  if (n > size)
    __chk_fail ();
  return memset (dst, c, n);
}

char *
strcpy (char *d, const char *s)
{
  char *r = d;




  while ((*d++ = *s++));
  return r;
}

char *
__strcpy_chk (char *d, const char *s, long unsigned int size)
{

  if (size == (long unsigned int) -1)
    abort ();
  ++chk_calls;
  if (strlen (s) >= size)
    __chk_fail ();
  return strcpy (d, s);
}

char *
stpcpy (char *dst, const char *src)
{





  while (*src != 0)
    *dst++ = *src++;

  *dst = 0;
  return dst;
}

char *
__stpcpy_chk (char *d, const char *s, long unsigned int size)
{

  if (size == (long unsigned int) -1)
    abort ();
  ++chk_calls;
  if (strlen (s) >= size)
    __chk_fail ();
  return stpcpy (d, s);
}

char *
stpncpy (char *dst, const char *src, long unsigned int n)
{





  for (; *src && n; n--)
    *dst++ = *src++;

  char *ret = dst;

  while (n--)
    *dst++ = 0;

  return ret;
}


char *
__stpncpy_chk (char *s1, const char *s2, long unsigned int n, long unsigned int size)
{

  if (size == (long unsigned int) -1)
    abort ();
  ++chk_calls;
  if (n > size)
    __chk_fail ();
  return stpncpy (s1, s2, n);
}

char *
strncpy (char *s1, const char *s2, long unsigned int n)
{
  char *dest = s1;




  for (; *s2 && n; n--)
    *s1++ = *s2++;
  while (n--)
    *s1++ = 0;
  return dest;
}

char *
__strncpy_chk (char *s1, const char *s2, long unsigned int n, long unsigned int size)
{

  if (size == (long unsigned int) -1)
    abort ();
  ++chk_calls;
  if (n > size)
    __chk_fail ();
  return strncpy (s1, s2, n);
}

char *
strcat (char *dst, const char *src)
{
  char *p = dst;






  while (*p)
    p++;
  while ((*p++ = *src++))
    ;
  return dst;
}

char *
__strcat_chk (char *d, const char *s, long unsigned int size)
{

  if (size == (long unsigned int) -1)
    abort ();
  ++chk_calls;
  if (strlen (d) + strlen (s) >= size)
    __chk_fail ();
  return strcat (d, s);
}

char *
strncat (char *s1, const char *s2, long unsigned int n)
{
  char *dest = s1;
  char c;




  while (*s1) s1++;
  c = '\0';
  while (n > 0)
    {
      c = *s2++;
      *s1++ = c;
      if (c == '\0')
 return dest;
      n--;
    }
  if (c != '\0')
    *s1 = '\0';
  return dest;
}

char *
__strncat_chk (char *d, const char *s, long unsigned int n, long unsigned int size)
{
  long unsigned int len = strlen (d), n1 = n;
  const char *s1 = s;


  if (size == (long unsigned int) -1)
    abort ();
  ++chk_calls;
  while (len < size && n1 > 0)
    {
      if (*s1++ == '\0')
 break;
      ++len;
      --n1;
    }

  if (len >= size)
    __chk_fail ();
  return strncat (d, s, n);
}




static char chk_sprintf_buf[4096];

int
__sprintf_chk (char *str, int flag, long unsigned int size, const char *fmt, ...)
{
  int ret;
  va_list ap;



  if (size == (long unsigned int) -1 && flag == 0)
    abort ();
  ++chk_calls;




  __builtin_va_start(ap,fmt);
  ret = vsprintf (chk_sprintf_buf, fmt, ap);
  __builtin_va_end(ap);
  if (ret >= 0)
    {
      if (ret >= size)
 __chk_fail ();
      memcpy (str, chk_sprintf_buf, ret + 1);
    }
  return ret;
}

int
__vsprintf_chk (char *str, int flag, long unsigned int size, const char *fmt,
  va_list ap)
{
  int ret;



  if (size == (long unsigned int) -1 && flag == 0)
    abort ();
  ++chk_calls;




  ret = vsprintf (chk_sprintf_buf, fmt, ap);
  if (ret >= 0)
    {
      if (ret >= size)
 __chk_fail ();
      memcpy (str, chk_sprintf_buf, ret + 1);
    }
  return ret;
}

int
__snprintf_chk (char *str, long unsigned int len, int flag, long unsigned int size,
  const char *fmt, ...)
{
  int ret;
  va_list ap;



  if (size == (long unsigned int) -1 && flag == 0)
    abort ();
  ++chk_calls;
  if (size < len)
    __chk_fail ();




  __builtin_va_start(ap,fmt);
  ret = vsprintf (chk_sprintf_buf, fmt, ap);
  __builtin_va_end(ap);
  if (ret >= 0)
    {
      if (ret < len)
 memcpy (str, chk_sprintf_buf, ret + 1);
      else
 {
   memcpy (str, chk_sprintf_buf, len - 1);
   str[len - 1] = '\0';
 }
    }
  return ret;
}

int
__vsnprintf_chk (char *str, long unsigned int len, int flag, long unsigned int size,
   const char *fmt, va_list ap)
{
  int ret;



  if (size == (long unsigned int) -1 && flag == 0)
    abort ();
  ++chk_calls;
  if (size < len)
    __chk_fail ();




  ret = vsprintf (chk_sprintf_buf, fmt, ap);
  if (ret >= 0)
    {
      if (ret < len)
 memcpy (str, chk_sprintf_buf, ret + 1);
      else
 {
   memcpy (str, chk_sprintf_buf, len - 1);
   str[len - 1] = '\0';
 }
    }
  return ret;
}

int
snprintf (char *str, long unsigned int len, const char *fmt, ...)
{
  int ret;
  va_list ap;





  __builtin_va_start(ap,fmt);
  ret = vsprintf (chk_sprintf_buf, fmt, ap);
  __builtin_va_end(ap);
  if (ret >= 0)
    {
      if (ret < len)
 memcpy (str, chk_sprintf_buf, ret + 1);
      else if (len)
 {
   memcpy (str, chk_sprintf_buf, len - 1);
   str[len - 1] = '\0';
 }
    }
  return ret;
}



int
vsnprintf (char *str, long unsigned int len, const char *fmt, va_list ap)
{
  int ret;





  ret = vsprintf (chk_sprintf_buf, fmt, ap);
  if (ret >= 0)
    {
      if (ret < len)
 memcpy (str, chk_sprintf_buf, ret + 1);
      else if (len)
 {
   memcpy (str, chk_sprintf_buf, len - 1);
   str[len - 1] = '\0';
 }
    }
  return ret;
}
