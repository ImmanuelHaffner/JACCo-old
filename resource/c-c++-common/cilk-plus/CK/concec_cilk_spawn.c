






int spawn_func (int arg)
{
  return arg + 1;
}

void func ()
{
  int a;
  a = _Cilk_spawn _Cilk_spawn spawn_func (4);
  a = _Cilk_spawn _Cilk_spawn _Cilk_spawn spawn_func (4);
  a = _Cilk_spawn _Cilk_spawn _Cilk_spawn _Cilk_spawn spawn_func (4);
  return;
}
