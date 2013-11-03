






__attribute__((vector_size(16) )) float a;
__attribute__((vector_size(16) )) int a1;

int f(void)
{
 a = ~a;
 a1 = ~a1;
}
