



extern void abort (void);
extern void exit (int);
struct { long long l; unsigned int i : 6, j : 11, k : 15; } b;
struct { long long l; unsigned int i : 5, j : 1, k : 26; } c;
struct { long long l; unsigned int i : 16, j : 8, k : 8; } d;

unsigned int ret1 (void) { return b.i; }
unsigned int ret2 (void) { return b.j; }
unsigned int ret3 (void) { return b.k; }
unsigned int ret4 (void) { return c.i; }
unsigned int ret5 (void) { return c.j; }
unsigned int ret6 (void) { return c.k; }
unsigned int ret7 (void) { return d.i; }
unsigned int ret8 (void) { return d.j; }
unsigned int ret9 (void) { return d.k; }
void fn1_1 (unsigned int x) { b.i += x; } void fn2_1 (unsigned int x) { b.j += x; } void fn3_1 (unsigned int x) { b.k += x; } void fn4_1 (unsigned int x) { c.i += x; } void fn5_1 (unsigned int x) { c.j += x; } void fn6_1 (unsigned int x) { c.k += x; } void fn7_1 (unsigned int x) { d.i += x; } void fn8_1 (unsigned int x) { d.j += x; } void fn9_1 (unsigned int x) { d.k += x; }
void fn1_2 (unsigned int x) { ++ b.i ; } void fn2_2 (unsigned int x) { ++ b.j ; } void fn3_2 (unsigned int x) { ++ b.k ; } void fn4_2 (unsigned int x) { ++ c.i ; } void fn5_2 (unsigned int x) { ++ c.j ; } void fn6_2 (unsigned int x) { ++ c.k ; } void fn7_2 (unsigned int x) { ++ d.i ; } void fn8_2 (unsigned int x) { ++ d.j ; } void fn9_2 (unsigned int x) { ++ d.k ; }
void fn1_3 (unsigned int x) { b.i ++; } void fn2_3 (unsigned int x) { b.j ++; } void fn3_3 (unsigned int x) { b.k ++; } void fn4_3 (unsigned int x) { c.i ++; } void fn5_3 (unsigned int x) { c.j ++; } void fn6_3 (unsigned int x) { c.k ++; } void fn7_3 (unsigned int x) { d.i ++; } void fn8_3 (unsigned int x) { d.j ++; } void fn9_3 (unsigned int x) { d.k ++; }
void fn1_4 (unsigned int x) { b.i -= x; } void fn2_4 (unsigned int x) { b.j -= x; } void fn3_4 (unsigned int x) { b.k -= x; } void fn4_4 (unsigned int x) { c.i -= x; } void fn5_4 (unsigned int x) { c.j -= x; } void fn6_4 (unsigned int x) { c.k -= x; } void fn7_4 (unsigned int x) { d.i -= x; } void fn8_4 (unsigned int x) { d.j -= x; } void fn9_4 (unsigned int x) { d.k -= x; }
void fn1_5 (unsigned int x) { -- b.i ; } void fn2_5 (unsigned int x) { -- b.j ; } void fn3_5 (unsigned int x) { -- b.k ; } void fn4_5 (unsigned int x) { -- c.i ; } void fn5_5 (unsigned int x) { -- c.j ; } void fn6_5 (unsigned int x) { -- c.k ; } void fn7_5 (unsigned int x) { -- d.i ; } void fn8_5 (unsigned int x) { -- d.j ; } void fn9_5 (unsigned int x) { -- d.k ; }
void fn1_6 (unsigned int x) { b.i --; } void fn2_6 (unsigned int x) { b.j --; } void fn3_6 (unsigned int x) { b.k --; } void fn4_6 (unsigned int x) { c.i --; } void fn5_6 (unsigned int x) { c.j --; } void fn6_6 (unsigned int x) { c.k --; } void fn7_6 (unsigned int x) { d.i --; } void fn8_6 (unsigned int x) { d.j --; } void fn9_6 (unsigned int x) { d.k --; }
void fn1_7 (unsigned int x) { b.i &= x; } void fn2_7 (unsigned int x) { b.j &= x; } void fn3_7 (unsigned int x) { b.k &= x; } void fn4_7 (unsigned int x) { c.i &= x; } void fn5_7 (unsigned int x) { c.j &= x; } void fn6_7 (unsigned int x) { c.k &= x; } void fn7_7 (unsigned int x) { d.i &= x; } void fn8_7 (unsigned int x) { d.j &= x; } void fn9_7 (unsigned int x) { d.k &= x; }
void fn1_8 (unsigned int x) { b.i |= x; } void fn2_8 (unsigned int x) { b.j |= x; } void fn3_8 (unsigned int x) { b.k |= x; } void fn4_8 (unsigned int x) { c.i |= x; } void fn5_8 (unsigned int x) { c.j |= x; } void fn6_8 (unsigned int x) { c.k |= x; } void fn7_8 (unsigned int x) { d.i |= x; } void fn8_8 (unsigned int x) { d.j |= x; } void fn9_8 (unsigned int x) { d.k |= x; }
void fn1_9 (unsigned int x) { b.i ^= x; } void fn2_9 (unsigned int x) { b.j ^= x; } void fn3_9 (unsigned int x) { b.k ^= x; } void fn4_9 (unsigned int x) { c.i ^= x; } void fn5_9 (unsigned int x) { c.j ^= x; } void fn6_9 (unsigned int x) { c.k ^= x; } void fn7_9 (unsigned int x) { d.i ^= x; } void fn8_9 (unsigned int x) { d.j ^= x; } void fn9_9 (unsigned int x) { d.k ^= x; }
void fn1_a (unsigned int x) { b.i /= x; } void fn2_a (unsigned int x) { b.j /= x; } void fn3_a (unsigned int x) { b.k /= x; } void fn4_a (unsigned int x) { c.i /= x; } void fn5_a (unsigned int x) { c.j /= x; } void fn6_a (unsigned int x) { c.k /= x; } void fn7_a (unsigned int x) { d.i /= x; } void fn8_a (unsigned int x) { d.j /= x; } void fn9_a (unsigned int x) { d.k /= x; }
void fn1_b (unsigned int x) { b.i %= x; } void fn2_b (unsigned int x) { b.j %= x; } void fn3_b (unsigned int x) { b.k %= x; } void fn4_b (unsigned int x) { c.i %= x; } void fn5_b (unsigned int x) { c.j %= x; } void fn6_b (unsigned int x) { c.k %= x; } void fn7_b (unsigned int x) { d.i %= x; } void fn8_b (unsigned int x) { d.j %= x; } void fn9_b (unsigned int x) { d.k %= x; }
void fn1_c (unsigned int x) { b.i += 3; } void fn2_c (unsigned int x) { b.j += 3; } void fn3_c (unsigned int x) { b.k += 3; } void fn4_c (unsigned int x) { c.i += 3; } void fn5_c (unsigned int x) { c.j += 3; } void fn6_c (unsigned int x) { c.k += 3; } void fn7_c (unsigned int x) { d.i += 3; } void fn8_c (unsigned int x) { d.j += 3; } void fn9_c (unsigned int x) { d.k += 3; }
void fn1_d (unsigned int x) { b.i -= 7; } void fn2_d (unsigned int x) { b.j -= 7; } void fn3_d (unsigned int x) { b.k -= 7; } void fn4_d (unsigned int x) { c.i -= 7; } void fn5_d (unsigned int x) { c.j -= 7; } void fn6_d (unsigned int x) { c.k -= 7; } void fn7_d (unsigned int x) { d.i -= 7; } void fn8_d (unsigned int x) { d.j -= 7; } void fn9_d (unsigned int x) { d.k -= 7; }
void fn1_e (unsigned int x) { b.i &= 21; } void fn2_e (unsigned int x) { b.j &= 21; } void fn3_e (unsigned int x) { b.k &= 21; } void fn4_e (unsigned int x) { c.i &= 21; } void fn5_e (unsigned int x) { c.j &= 21; } void fn6_e (unsigned int x) { c.k &= 21; } void fn7_e (unsigned int x) { d.i &= 21; } void fn8_e (unsigned int x) { d.j &= 21; } void fn9_e (unsigned int x) { d.k &= 21; }
void fn1_f (unsigned int x) { b.i |= 19; } void fn2_f (unsigned int x) { b.j |= 19; } void fn3_f (unsigned int x) { b.k |= 19; } void fn4_f (unsigned int x) { c.i |= 19; } void fn5_f (unsigned int x) { c.j |= 19; } void fn6_f (unsigned int x) { c.k |= 19; } void fn7_f (unsigned int x) { d.i |= 19; } void fn8_f (unsigned int x) { d.j |= 19; } void fn9_f (unsigned int x) { d.k |= 19; }
void fn1_g (unsigned int x) { b.i ^= 37; } void fn2_g (unsigned int x) { b.j ^= 37; } void fn3_g (unsigned int x) { b.k ^= 37; } void fn4_g (unsigned int x) { c.i ^= 37; } void fn5_g (unsigned int x) { c.j ^= 37; } void fn6_g (unsigned int x) { c.k ^= 37; } void fn7_g (unsigned int x) { d.i ^= 37; } void fn8_g (unsigned int x) { d.j ^= 37; } void fn9_g (unsigned int x) { d.k ^= 37; }
void fn1_h (unsigned int x) { b.i /= 17; } void fn2_h (unsigned int x) { b.j /= 17; } void fn3_h (unsigned int x) { b.k /= 17; } void fn4_h (unsigned int x) { c.i /= 17; } void fn5_h (unsigned int x) { c.j /= 17; } void fn6_h (unsigned int x) { c.k /= 17; } void fn7_h (unsigned int x) { d.i /= 17; } void fn8_h (unsigned int x) { d.j /= 17; } void fn9_h (unsigned int x) { d.k /= 17; }
void fn1_i (unsigned int x) { b.i %= 19; } void fn2_i (unsigned int x) { b.j %= 19; } void fn3_i (unsigned int x) { b.k %= 19; } void fn4_i (unsigned int x) { c.i %= 19; } void fn5_i (unsigned int x) { c.j %= 19; } void fn6_i (unsigned int x) { c.k %= 19; } void fn7_i (unsigned int x) { d.i %= 19; } void fn8_i (unsigned int x) { d.j %= 19; } void fn9_i (unsigned int x) { d.k %= 19; }




int
main (void)
{
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_1 (3); if (ret1 () != ((51 + 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_1 (251); if (ret2 () != ((636 + 251) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_1 (13279); if (ret3 () != ((31278 + 13279) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_1 (24); if (ret4 () != ((21 + 24) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_1 (1); if (ret5 () != ((1 + 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_1 (264151); if (ret6 () != ((33554432 + 264151) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_1 (713); if (ret7 () != ((26812 + 713) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_1 (17); if (ret8 () != ((156 + 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_1 (199); if (ret9 () != ((187 + 199) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_2 (3); if (ret1 () != ((51 + 1) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_2 (251); if (ret2 () != ((636 + 1) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_2 (13279); if (ret3 () != ((31278 + 1) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_2 (24); if (ret4 () != ((21 + 1) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_2 (1); if (ret5 () != ((1 + 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_2 (264151); if (ret6 () != ((33554432 + 1) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_2 (713); if (ret7 () != ((26812 + 1) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_2 (17); if (ret8 () != ((156 + 1) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_2 (199); if (ret9 () != ((187 + 1) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_3 (3); if (ret1 () != ((51 + 1) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_3 (251); if (ret2 () != ((636 + 1) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_3 (13279); if (ret3 () != ((31278 + 1) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_3 (24); if (ret4 () != ((21 + 1) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_3 (1); if (ret5 () != ((1 + 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_3 (264151); if (ret6 () != ((33554432 + 1) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_3 (713); if (ret7 () != ((26812 + 1) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_3 (17); if (ret8 () != ((156 + 1) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_3 (199); if (ret9 () != ((187 + 1) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_4 (3); if (ret1 () != ((51 - 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_4 (251); if (ret2 () != ((636 - 251) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_4 (13279); if (ret3 () != ((31278 - 13279) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_4 (24); if (ret4 () != ((21 - 24) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_4 (1); if (ret5 () != ((1 - 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_4 (264151); if (ret6 () != ((33554432 - 264151) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_4 (713); if (ret7 () != ((26812 - 713) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_4 (17); if (ret8 () != ((156 - 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_4 (199); if (ret9 () != ((187 - 199) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_5 (3); if (ret1 () != ((51 - 1) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_5 (251); if (ret2 () != ((636 - 1) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_5 (13279); if (ret3 () != ((31278 - 1) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_5 (24); if (ret4 () != ((21 - 1) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_5 (1); if (ret5 () != ((1 - 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_5 (264151); if (ret6 () != ((33554432 - 1) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_5 (713); if (ret7 () != ((26812 - 1) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_5 (17); if (ret8 () != ((156 - 1) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_5 (199); if (ret9 () != ((187 - 1) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_6 (3); if (ret1 () != ((51 - 1) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_6 (251); if (ret2 () != ((636 - 1) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_6 (13279); if (ret3 () != ((31278 - 1) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_6 (24); if (ret4 () != ((21 - 1) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_6 (1); if (ret5 () != ((1 - 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_6 (264151); if (ret6 () != ((33554432 - 1) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_6 (713); if (ret7 () != ((26812 - 1) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_6 (17); if (ret8 () != ((156 - 1) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_6 (199); if (ret9 () != ((187 - 1) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_7 (3); if (ret1 () != ((51 & 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_7 (251); if (ret2 () != ((636 & 251) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_7 (13279); if (ret3 () != ((31278 & 13279) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_7 (24); if (ret4 () != ((21 & 24) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_7 (1); if (ret5 () != ((1 & 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_7 (264151); if (ret6 () != ((33554432 & 264151) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_7 (713); if (ret7 () != ((26812 & 713) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_7 (17); if (ret8 () != ((156 & 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_7 (199); if (ret9 () != ((187 & 199) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_8 (3); if (ret1 () != ((51 | 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_8 (251); if (ret2 () != ((636 | 251) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_8 (13279); if (ret3 () != ((31278 | 13279) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_8 (24); if (ret4 () != ((21 | 24) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_8 (1); if (ret5 () != ((1 | 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_8 (264151); if (ret6 () != ((33554432 | 264151) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_8 (713); if (ret7 () != ((26812 | 713) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_8 (17); if (ret8 () != ((156 | 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_8 (199); if (ret9 () != ((187 | 199) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_9 (3); if (ret1 () != ((51 ^ 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_9 (251); if (ret2 () != ((636 ^ 251) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_9 (13279); if (ret3 () != ((31278 ^ 13279) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_9 (24); if (ret4 () != ((21 ^ 24) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_9 (1); if (ret5 () != ((1 ^ 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_9 (264151); if (ret6 () != ((33554432 ^ 264151) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_9 (713); if (ret7 () != ((26812 ^ 713) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_9 (17); if (ret8 () != ((156 ^ 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_9 (199); if (ret9 () != ((187 ^ 199) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_a (3); if (ret1 () != ((51 / 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_a (251); if (ret2 () != ((636 / 251) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_a (13279); if (ret3 () != ((31278 / 13279) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_a (24); if (ret4 () != ((21 / 24) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_a (1); if (ret5 () != ((1 / 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_a (264151); if (ret6 () != ((33554432 / 264151) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_a (713); if (ret7 () != ((26812 / 713) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_a (17); if (ret8 () != ((156 / 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_a (199); if (ret9 () != ((187 / 199) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_b (3); if (ret1 () != ((51 % 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_b (251); if (ret2 () != ((636 % 251) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_b (13279); if (ret3 () != ((31278 % 13279) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_b (24); if (ret4 () != ((21 % 24) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_b (1); if (ret5 () != ((1 % 1) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_b (264151); if (ret6 () != ((33554432 % 264151) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_b (713); if (ret7 () != ((26812 % 713) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_b (17); if (ret8 () != ((156 % 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_b (199); if (ret9 () != ((187 % 199) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_c (3); if (ret1 () != ((51 + 3) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_c (251); if (ret2 () != ((636 + 3) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_c (13279); if (ret3 () != ((31278 + 3) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_c (24); if (ret4 () != ((21 + 3) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_c (1); if (ret5 () != ((1 + 3) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_c (264151); if (ret6 () != ((33554432 + 3) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_c (713); if (ret7 () != ((26812 + 3) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_c (17); if (ret8 () != ((156 + 3) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_c (199); if (ret9 () != ((187 + 3) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_d (3); if (ret1 () != ((51 - 7) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_d (251); if (ret2 () != ((636 - 7) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_d (13279); if (ret3 () != ((31278 - 7) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_d (24); if (ret4 () != ((21 - 7) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_d (1); if (ret5 () != ((1 - 7) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_d (264151); if (ret6 () != ((33554432 - 7) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_d (713); if (ret7 () != ((26812 - 7) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_d (17); if (ret8 () != ((156 - 7) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_d (199); if (ret9 () != ((187 - 7) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_e (3); if (ret1 () != ((51 & 21) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_e (251); if (ret2 () != ((636 & 21) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_e (13279); if (ret3 () != ((31278 & 21) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_e (24); if (ret4 () != ((21 & 21) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_e (1); if (ret5 () != ((1 & 21) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_e (264151); if (ret6 () != ((33554432 & 21) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_e (713); if (ret7 () != ((26812 & 21) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_e (17); if (ret8 () != ((156 & 21) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_e (199); if (ret9 () != ((187 & 21) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_f (3); if (ret1 () != ((51 | 19) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_f (251); if (ret2 () != ((636 | 19) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_f (13279); if (ret3 () != ((31278 | 19) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_f (24); if (ret4 () != ((21 | 19) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_f (1); if (ret5 () != ((1 | 19) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_f (264151); if (ret6 () != ((33554432 | 19) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_f (713); if (ret7 () != ((26812 | 19) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_f (17); if (ret8 () != ((156 | 19) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_f (199); if (ret9 () != ((187 | 19) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_g (3); if (ret1 () != ((51 ^ 37) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_g (251); if (ret2 () != ((636 ^ 37) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_g (13279); if (ret3 () != ((31278 ^ 37) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_g (24); if (ret4 () != ((21 ^ 37) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_g (1); if (ret5 () != ((1 ^ 37) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_g (264151); if (ret6 () != ((33554432 ^ 37) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_g (713); if (ret7 () != ((26812 ^ 37) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_g (17); if (ret8 () != ((156 ^ 37) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_g (199); if (ret9 () != ((187 ^ 37) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_h (3); if (ret1 () != ((51 / 17) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_h (251); if (ret2 () != ((636 / 17) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_h (13279); if (ret3 () != ((31278 / 17) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_h (24); if (ret4 () != ((21 / 17) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_h (1); if (ret5 () != ((1 / 17) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_h (264151); if (ret6 () != ((33554432 / 17) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_h (713); if (ret7 () != ((26812 / 17) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_h (17); if (ret8 () != ((156 / 17) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_h (199); if (ret9 () != ((187 / 17) & ((1 << 8) - 1))) abort (); d.k = 187;
b.i = 51; b.j = 636; b.k = 31278; c.i = 21; c.j = 1; c.k = 33554432; d.i = 26812; d.j = 156; d.k = 187; fn1_i (3); if (ret1 () != ((51 % 19) & ((1 << 6) - 1))) abort (); b.i = 51; fn2_i (251); if (ret2 () != ((636 % 19) & ((1 << 11) - 1))) abort (); b.j = 636; fn3_i (13279); if (ret3 () != ((31278 % 19) & ((1 << 15) - 1))) abort (); b.j = 31278; fn4_i (24); if (ret4 () != ((21 % 19) & ((1 << 5) - 1))) abort (); c.i = 21; fn5_i (1); if (ret5 () != ((1 % 19) & ((1 << 1) - 1))) abort (); c.j = 1; fn6_i (264151); if (ret6 () != ((33554432 % 19) & ((1 << 26) - 1))) abort (); c.k = 33554432; fn7_i (713); if (ret7 () != ((26812 % 19) & ((1 << 16) - 1))) abort (); d.i = 26812; fn8_i (17); if (ret8 () != ((156 % 19) & ((1 << 8) - 1))) abort (); d.j = 156; fn9_i (199); if (ret9 () != ((187 % 19) & ((1 << 8) - 1))) abort (); d.k = 187;

  return 0;
}