#include "ngram.h"


SEXP R_ngram_gen(SEXP ngl_ptr, SEXP genlen, SEXP seed)
{
  rng_state_t rs;
  SEXP RET;
  ngramlist_t *ngl = (ngramlist_t *) getRptr(ngl_ptr);
  int retlen;
  char *ret;
  
  rng_prepare(&rs);
  rng_set_type(&rs, RNG_TYPE_MT);
  rng_init(&rs, INT(seed));
  
  retlen = ngram_gen(&rs, ngl, INT(genlen), &ret);
  
  PROTECT(RET = allocVector(STRSXP, 1));
  SET_STRING_ELT(RET, 0, mkCharLen(ret, retlen));
  
  UNPROTECT(1);
  return RET;
}

