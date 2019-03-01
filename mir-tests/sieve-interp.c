#include "../mir-interp.h"
#include "scan-sieve.h"
#include "real-time.h"

#include <inttypes.h>

int main (void) {
  MIR_module_t m;
  MIR_item_t func;
  MIR_val_t val;
  double start_time;
    
  MIR_init ();
  func = create_mir_func_sieve (NULL, &m);
#if MIR_INTERP_DEBUG 
  fprintf (stderr, "\n++++++ SIEVE before simplification:\n");
  MIR_output (stderr);
#endif
  start_time = real_sec_time ();
  MIR_simplify_func (func);
#if MIR_INTERP_DEBUG 
  fprintf (stderr, "++++++ SIEVE after simplification:\n");
  MIR_output (stderr);
#endif
  MIR_load_module (m);
  MIR_link ();
  MIR_interp_init ();
  fprintf (stderr, "Interpreter init finish: %.3f ms\n", (real_sec_time () - start_time) * 1000.0);
  start_time = real_sec_time ();
  val = MIR_interp (func, 0);
  fprintf (stderr, "SIEVE -> %"PRId64 ": %.3f sec\n", val.i, real_sec_time () - start_time);
  MIR_interp_finish ();
  MIR_finish ();
  return 0;
}