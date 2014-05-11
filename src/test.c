#include "ngram.h"
#include "ngram/src/rand/rand.h"


SEXP ng_test(SEXP ng_ptr, SEXP ngsize_)
{
  rng_state_t rs;
  SEXP RET;
  ngram_t *ng = (ngram_t *) getRptr(ng_ptr);
  const int ngsize = INTEGER(ngsize_)[0];
  
  rng_prepare(&rs);
  rng_set_type(&rs, RNG_TYPE_MT);
  rng_init(&rs, 1234);
  
  gen(&rs, ng, ngsize, 5);
  
  return R_NilValue;
}

