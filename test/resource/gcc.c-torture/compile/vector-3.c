
__attribute__((vector_size(16) )) float g(void)
{
  float t = 1.0f;
  return (__attribute__((vector_size(16) )) float){0.0, 0.0, t, 0.0};
}
