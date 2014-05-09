#include "ngram.h"


SEXP ng_extract_ngrams(SEXP ng_ptr, SEXP ngsize_)
{
  int i, j, len;
  char *buf;
  ngram_t *ng = (ngram_t *) getRptr(ng_ptr);
  const int ngsize = INTEGER(ngsize_)[0];
  wordlist_t *wl;
  
  SEXP RET;
  PROTECT(RET = allocVector(STRSXP, ngsize));
  
  
  for(i=0; i<ngsize; i++)
  {
    len = 0;
    wl = ng[i].words;
    
    while (wl)
    {
      len += wl->word->len;
      len++; // spaces
      wl = wl->next;
    }
    
    len--; // apparently mkCharLen handles the NUL terminator for some reason
    
    buf = malloc(len * sizeof(buf));
    
    for (j=0; j<len; j++)
      buf[j] = ng[i].words->word->s[j];
    
    SET_STRING_ELT(RET, i, mkCharLen(buf, len));
    
    
    free(buf);
  }
  
  UNPROTECT(1);
  return RET;
}




SEXP ng_extract_str(SEXP str_ptr, SEXP R_strlen)
{
  SEXP RET;
  char *str = (char *) getRptr(str_ptr);
  
  PROTECT(RET = allocVector(STRSXP, 1));
  
  SET_STRING_ELT(RET, 0, mkCharLen(str, INTEGER(R_strlen)[0]));
  
  UNPROTECT(1);
  return RET;
}


