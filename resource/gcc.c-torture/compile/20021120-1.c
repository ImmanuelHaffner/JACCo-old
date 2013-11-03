





extern int inline foo () { return 0; }
extern int inline bar () { return 0; }
static int inline bar () { return foo(); }
