


struct timeval
{
  int tv_sec;
  int tv_usec;
};
void
capture_next_packet (void)
{
  struct timeval past, now, then;
  __builtin_bcopy (&then, &past, sizeof (then));
}
