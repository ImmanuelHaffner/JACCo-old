


extern void link_error (void);

int
main ()
{

  if (-2.0dl < -2.0dl)
    link_error ();


  if (-2.0dl >= .01dl)
    link_error ();


  if (0.2dd > 0.02e1dd)
    link_error ();


  if (-.000005dd >= -.0000049DL)
  link_error();


  if (__builtin_isless(-2.0dl,-2.0dl))
    link_error();

  if (__builtin_isgreaterequal(-2.0dl,.01dl))
    link_error();

  if (!(__builtin_islessequal(-2.0dl, -2.0dd)))
    link_error();

  if (!(__builtin_isgreater(2.0dl, -2.0dd)))
    link_error();

  if (__builtin_islessequal(2.0df, __builtin_nand64("")))
    link_error();

  if (__builtin_islessgreater(2.0dd, __builtin_nand64("")))
    link_error();

  if (!__builtin_islessgreater(2.0dd, -2.0dd))
    link_error();

  if (!__builtin_islessgreater(-3.0dd, 2.0dd))
    link_error();

  if (__builtin_isunordered(1.1df, 0.003dd))
    link_error();

  if (!__builtin_isunordered(-3.1df, __builtin_nand32("")))
    link_error();

  return 0;
}
