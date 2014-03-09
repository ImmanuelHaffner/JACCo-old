9


int main()
{
  struct O
  {
    int x;
    int zzz;
  };
  struct O o;
  struct O *po;
  po = &o;
  po->x = 4;
  po->zzz = 5;
  return po->x + po->zzz;
}
