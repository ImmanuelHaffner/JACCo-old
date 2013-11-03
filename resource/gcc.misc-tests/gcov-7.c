



















typedef long int __jmp_buf[8];
typedef int __sig_atomic_t;




typedef struct
  {
    unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
  } __sigset_t;



struct __jmp_buf_tag
  {




    __jmp_buf __jmpbuf;
    int __mask_was_saved;
    __sigset_t __saved_mask;
  };




typedef struct __jmp_buf_tag jmp_buf[1];



extern int setjmp (jmp_buf __env) __attribute__ ((__nothrow__));






extern int __sigsetjmp (struct __jmp_buf_tag __env[1], int __savemask) __attribute__ ((__nothrow__));




extern int _setjmp (struct __jmp_buf_tag __env[1]) __attribute__ ((__nothrow__));




extern void longjmp (struct __jmp_buf_tag __env[1], int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));







extern void _longjmp (struct __jmp_buf_tag __env[1], int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));







typedef struct __jmp_buf_tag sigjmp_buf[1];
extern void siglongjmp (sigjmp_buf __env, int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));


extern void abort (void);
extern void exit (int);

jmp_buf env;
int val;
int longjmp_taken;
int bar_enter, bar_exit;
int foo_enter, foo_exit;

void bar (int i)
{
  bar_enter++;

  if (i == 0) {

      longjmp_taken++;
      longjmp (env, 1);
    }
  val += i+1;
  bar_exit++;
}

void foo (int i)
{
  foo_enter++;

  if (i == 1) {

      longjmp_taken++;
      longjmp (env, 2);
    }

  bar (i);

  bar (7);

  val += 16;
  foo_exit++;
}

int
passed ()
{
  return (val == 31 &&
          longjmp_taken == 2 &&
   foo_enter == 3 &&
   foo_exit == 1 &&
   bar_enter == 3 &&
   bar_exit == 2);

}

void
leave (int i)
{
  if (i == 0) {
      abort ();
    }
  exit (0);
}

int
main()
{
  int retval;


  if ((retval = _setjmp (env))) {

      val += retval;
    }

  foo (val);

  leave (passed());

}
