
struct b{};
f(struct b(*f)())
{
struct b d=f();
}
