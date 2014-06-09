#include "ngram.h"


SEXP R_mix_96(SEXP a, SEXP b, SEXP c)
{
  SEXP ret;
  PROTECT(ret = allocVector(INTSXP, 1));
  
  INT(ret) = mix_96(INT(a), INT(b), INT(c));
  
  UNPROTECT(1);
  return ret;
}


uint32_t ngram_get_seed();

SEXP R_ngram_get_seed()
{
  SEXP ret;
  PROTECT(ret = allocVector(INTSXP, 1));
  
  INT(ret) = (int) ngram_get_seed();
  
  UNPROTECT(1);
  return ret;
}
