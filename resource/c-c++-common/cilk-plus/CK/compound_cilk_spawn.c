int spawn_func (int arg)
{
  return arg + 1;
}

int check()
{
  int z;
  z = 23, _Cilk_spawn spawn_func (3), 3424;
  23, spawn_func (5), _Cilk_spawn spawn_func (3);
  _Cilk_spawn spawn_func (0), _Cilk_spawn spawn_func (3), 3, spawn_func (0);
  return 23;
}
