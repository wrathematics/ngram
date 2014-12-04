#include "ngram.h"


// With inspiration from Martin Morgan
static void str_finalize(SEXP ptr)
{
  if (NULL == R_ExternalPtrAddr(ptr))
    return;
  
  char *str = (char *) R_ExternalPtrAddr(ptr);
  free(str);
  R_ClearExternalPtr(ptr);
}

static void wl_finalize(SEXP ptr)
{
  if (NULL == R_ExternalPtrAddr(ptr))
    return;
  
  wordlist_t *wl = (wordlist_t *) R_ExternalPtrAddr(ptr);
  free_wordlist(wl);
  R_ClearExternalPtr(ptr);
}

void free_ngl(ngramlist_t *ngl);

static void ngl_finalize(SEXP ptr)
{
  if (NULL == R_ExternalPtrAddr(ptr))
    return;
  
  ngramlist_t *ngl = (ngramlist_t *) R_ExternalPtrAddr(ptr);
  free_ngl(ngl);
  R_ClearExternalPtr(ptr);
}



SEXP ng_process(SEXP R_str, SEXP R_str_len, SEXP n_)
{
  char *str;
  const int n = INTEGER(n_)[0];
  wordlist_t *wl;
  ngramlist_t *ngl;
  
  SEXP RET, RET_NAMES, NGSIZE;
  SEXP str_ptr, wl_ptr, ngl_ptr;
  
  
  str = malloc((INTEGER(R_str_len)[0]+1) * sizeof(str));
  strcpy(str, CHARPT(R_str, 0));
  
  wl = lex(str, strlen(str));
  ngl = process(wl, n);
  
  if (NULL == ngl)
  {
    PROTECT(RET = allocVector(INTSXP, 1));
    INTEGER(RET)[0] = -1;
    UNPROTECT(1);
    
    free(str);
    
    return RET;
  }
  
  newRptr(str, str_ptr, str_finalize);
  newRptr(wl, wl_ptr, wl_finalize);
  newRptr(ngl, ngl_ptr, ngl_finalize);
  
  // Wrangle the list
  PROTECT(NGSIZE = allocVector(INTSXP, 1));
  INTEGER(NGSIZE)[0] = ngl->ngsize;
  
  PROTECT(RET = allocVector(VECSXP, 4));
  PROTECT(RET_NAMES = allocVector(STRSXP, 4));
  
  SET_VECTOR_ELT(RET, 0, str_ptr);
  SET_VECTOR_ELT(RET, 1, wl_ptr);
  SET_VECTOR_ELT(RET, 2, ngl_ptr);
  SET_VECTOR_ELT(RET, 3, NGSIZE);
  
  SET_STRING_ELT(RET_NAMES, 0, mkChar("str_ptr"));
  SET_STRING_ELT(RET_NAMES, 1, mkChar("wl_ptr"));
  SET_STRING_ELT(RET_NAMES, 2, mkChar("ngl_ptr"));
  SET_STRING_ELT(RET_NAMES, 3, mkChar("ngsize"));
  
  setAttrib(RET, R_NamesSymbol, RET_NAMES);
  
  UNPROTECT(6);
  return RET;
}


