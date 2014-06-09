#include "ngram.h"


SEXP R_ngram_wordcount(SEXP str, SEXP sep)
{
  SEXP ret;
  PROTECT(ret = allocVector(INTSXP, 1));
  
  INT(ret) = ngram_wordcount(CHARPT(str, 0), CHARPT(sep, 0)[0]);
  
  UNPROTECT(1);
  return ret;
}
