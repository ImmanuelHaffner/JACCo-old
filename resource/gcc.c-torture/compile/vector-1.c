

struct ss
{
 __attribute__((vector_size(16) )) float mVec;
};
float getCapsule(__attribute__((vector_size(16) )) int t)
{
 __attribute__((vector_size(16) )) float t1 = (__attribute__((vector_size(16) )) float)t;
 struct ss y = {t1};
 return *((float*)&y.mVec);
}
