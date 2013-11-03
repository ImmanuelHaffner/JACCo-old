


int failures;

extern void link_error (void);

int
main ()
{

  if (2.0df != 2.0df)
    link_error ();


  if (500e-2dl != 0.05e2df)
    link_error ();


  if (1.4 + 1.4 + 1.4 == 4.2)
    link_error ();


  if (1.4dd + 1.4dd + 1.4dd != 4.2dd)
    link_error ();

  return 0;
}
