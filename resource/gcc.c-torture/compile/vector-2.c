

struct ss
{
 __attribute__((vector_size(16) )) float mVec;
};
__attribute__((vector_size(16) )) float getCapsule(__attribute__((vector_size(16) )) int t)
{
 __attribute__((vector_size(16) )) float t1 = (__attribute__((vector_size(16) )) float)t;
 struct ss y = {t1};
 *((float*)&y.mVec) = 1.0;
 return y.mVec;
}
