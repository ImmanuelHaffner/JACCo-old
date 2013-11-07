





__attribute__((vector_size(16) )) float a;
__attribute__((vector_size(16) )) int a1;
__attribute__((vector_size(16) )) float b;
__attribute__((vector_size(16) )) int b1;

int f(void)
{
 a = a | b;
 a = a & b;
 a = a ^ b;
 a1 = a1 | b1;
 a1 = a1 & b1;
 a1 = a1 ^ b1;
}
