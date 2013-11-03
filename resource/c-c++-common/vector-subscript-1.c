





float vf(__attribute__((vector_size(16) )) float a)
{
  return 0[a];
}


float fv(__attribute__((vector_size(16) )) float a)
{
  return a[0];
}
