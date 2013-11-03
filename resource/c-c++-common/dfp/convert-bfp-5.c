


int failures;

volatile _Decimal32 sd;
volatile _Decimal64 dd;
volatile _Decimal128 td;
volatile float sf;
volatile double df;
volatile long double tf;

void convert_t_sdsf_nan (void) { ; sd = __builtin_nand32 (""); sf = sd; if (__builtin_isnanf (sf) == 0) __builtin_abort ();; } void convert_t_sddf_nan (void) { ; sd = __builtin_nand32 (""); df = sd; if (__builtin_isnan (df) == 0) __builtin_abort ();; } void convert_t_ddsf_nan (void) { ; dd = __builtin_nand64 (""); sf = dd; if (__builtin_isnanf (sf) == 0) __builtin_abort ();; } void convert_t_dddf_nan (void) { ; dd = __builtin_nand64 (""); df = dd; if (__builtin_isnan (df) == 0) __builtin_abort ();; } void convert_t_tdsf_nan (void) { ; td = __builtin_nand128 (""); sf = td; if (__builtin_isnanf (sf) == 0) __builtin_abort ();; } void convert_t_tddf_nan (void) { ; td = __builtin_nand128 (""); df = td; if (__builtin_isnan (df) == 0) __builtin_abort ();; } void convert_t_sfsd_nan (void) { ; sf = __builtin_nanf (""); sd = sf; if (__builtin_isnand32 (sd) == 0) __builtin_abort ();; } void convert_t_sfdd_nan (void) { ; sf = __builtin_nanf (""); dd = sf; if (__builtin_isnand64 (dd) == 0) __builtin_abort ();; } void convert_t_sftd_nan (void) { ; sf = __builtin_nanf (""); td = sf; if (__builtin_isnand128 (td) == 0) __builtin_abort ();; } void convert_t_dfsd_nan (void) { ; df = __builtin_nan (""); sd = df; if (__builtin_isnand32 (sd) == 0) __builtin_abort ();; } void convert_t_dfdd_nan (void) { ; df = __builtin_nan (""); dd = df; if (__builtin_isnand64 (dd) == 0) __builtin_abort ();; } void convert_t_dftd_nan (void) { ; df = __builtin_nan (""); td = df; if (__builtin_isnand128 (td) == 0) __builtin_abort ();; } void convert_t_sddd_nan (void) { ; sd = __builtin_nand32 (""); dd = sd; if (__builtin_isnand64 (dd) == 0) __builtin_abort ();; } void convert_t_sdtd_nan (void) { ; sd = __builtin_nand32 (""); td = sd; if (__builtin_isnand128 (td) == 0) __builtin_abort ();; } void convert_t_ddsd_nan (void) { ; dd = __builtin_nand64 (""); sd = dd; if (__builtin_isnand32 (sd) == 0) __builtin_abort ();; } void convert_t_ddtd_nan (void) { ; dd = __builtin_nand64 (""); td = dd; if (__builtin_isnand128 (td) == 0) __builtin_abort ();; } void convert_t_tdsd_nan (void) { ; td = __builtin_nand128 (""); sd = td; if (__builtin_isnand32 (sd) == 0) __builtin_abort ();; } void convert_t_tddd_nan (void) { ; td = __builtin_nand128 (""); dd = td; if (__builtin_isnand64 (dd) == 0) __builtin_abort ();; } void convert_t_sdtf_nan (void) { ; sd = __builtin_nand32 (""); tf = sd; if (__builtin_isnanl (tf) == 0) __builtin_abort ();; } void convert_t_ddtf_nan (void) { ; dd = __builtin_nand64 (""); tf = dd; if (__builtin_isnanl (tf) == 0) __builtin_abort ();; } void convert_t_tdtf_nan (void) { ; td = __builtin_nand128 (""); tf = td; if (__builtin_isnanl (tf) == 0) __builtin_abort ();; } void convert_t_tfsd_nan (void) { ; tf = __builtin_nanl (""); sd = tf; if (__builtin_isnand32 (sd) == 0) __builtin_abort ();; } void convert_t_tfdd_nan (void) { ; tf = __builtin_nanl (""); dd = tf; if (__builtin_isnand64 (dd) == 0) __builtin_abort ();; } void convert_t_tftd_nan (void) { ; tf = __builtin_nanl (""); td = tf; if (__builtin_isnand128 (td) == 0) __builtin_abort ();; };

int
main ()
{
  convert_t_sdsf_nan (); convert_t_sddf_nan (); convert_t_ddsf_nan (); convert_t_dddf_nan (); convert_t_tdsf_nan (); convert_t_tddf_nan (); convert_t_sfsd_nan (); convert_t_sfdd_nan (); convert_t_sftd_nan (); convert_t_dfsd_nan (); convert_t_dfdd_nan (); convert_t_dftd_nan (); convert_t_sddd_nan (); convert_t_sdtd_nan (); convert_t_ddsd_nan (); convert_t_ddtd_nan (); convert_t_tdsd_nan (); convert_t_tddd_nan (); convert_t_sdtf_nan (); convert_t_ddtf_nan (); convert_t_tdtf_nan (); convert_t_tfsd_nan (); convert_t_tfdd_nan (); convert_t_tftd_nan ();

  return 0;
}
