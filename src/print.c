#include "ngram.h"

SEXP ng_print(SEXP ng_ptr, SEXP ngsize_)
{
  int i;
  ngram_t *ng = (ngram_t *) getRptr(ng_ptr);
  const int ngsize = INTEGER(ngsize_)[0];
  
  for(i=0; i<ngsize; i++)
    print_ngram(ng + i);
  
  return R_NilValue;
}

