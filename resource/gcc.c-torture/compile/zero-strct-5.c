


struct f {};
struct g1 {struct f l;};

static inline void g(struct f a, int i){}

void h(void)
{
  struct g1 t;
  g(t.l , 1);
}
