#include "ngram.h"
#include "ngram/src/rand/rand.h"


SEXP ng_test(SEXP ng_ptr, SEXP ngsize_, SEXP genlen)
{
  rng_state_t rs;
  SEXP RET;
  ngram_t *ng = (ngram_t *) getRptr(ng_ptr);
  const int ngsize = INTEGER(ngsize_)[0];
  int len;
  char *ret;
  
  rng_prepare(&rs);
  rng_set_type(&rs, RNG_TYPE_MT);
  rng_init(&rs, 1234);
  
  len = gen(&rs, ng, ngsize, INTEGER(genlen)[0], &ret);
  
  PROTECT(RET = allocVector(STRSXP, 1));
  SET_STRING_ELT(RET, 0, mkCharLen(ret, len-1));
  
  UNPROTECT(1);
  return RET;
}

