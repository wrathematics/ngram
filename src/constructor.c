#include "ngram.h"


// With inspiration from Martin Morgan
static void str_finalize(SEXP ptr)
{
  if (NULL == R_ExternalPtrAddr(ptr))
    return;
  
/*  Rprintf("str\n");*/
  
  char *str = (char *) R_ExternalPtrAddr(ptr);
  free(str);
  R_ClearExternalPtr(ptr);
}

static void wl_finalize(SEXP ptr)
{
  if (NULL == R_ExternalPtrAddr(ptr))
    return;
  
/*  Rprintf("wl\n");*/
  
  wordlist_t *wl = (wordlist_t *) R_ExternalPtrAddr(ptr);
  free_wordlist(wl);
  R_ClearExternalPtr(ptr);
}

void free_nga(ng_arr_t *ng);

static void ng_finalize(SEXP ptr)
{
  if (NULL == R_ExternalPtrAddr(ptr))
    return;
  
/*  Rprintf("ng\n");*/
  
  ng_arr_t *ng = (ng_arr_t *) R_ExternalPtrAddr(ptr);
  free_nga(ng);
  R_ClearExternalPtr(ptr);
}



SEXP ng_process(SEXP R_str, SEXP R_str_len, SEXP n_)
{
  char *str;
  const int n = INTEGER(n_)[0];
  wordlist_t *wl;
  ngram_t *ng;
  ng_arr_t *nga;
  nga = malloc(sizeof(*nga));
  int ngsize;
  
  str = malloc((INTEGER(R_str_len)[0]+1) * sizeof(str));
  strcpy(str, CHARPT(R_str, 0));
  
  SEXP RET, RET_NAMES, NGSIZE;
  SEXP str_ptr, wl_ptr, ng_ptr;
  
  
  wl = lex(str, strlen(str));
  ng = process(wl, n, &ngsize);
  
  nga->ng = ng;
  nga->ngsize = ngsize;
  
  if (NULL == ng)
  {
    PROTECT(RET = allocVector(INTSXP, 1));
    INTEGER(RET)[0] = -1;
    UNPROTECT(1);
    
    free(str);
    
    return RET;
  }
  
  newRptr(str, str_ptr, str_finalize);
  newRptr(wl, wl_ptr, wl_finalize);
  newRptr(nga, ng_ptr, ng_finalize);
  
  // Wrangle the list
  PROTECT(NGSIZE = allocVector(INTSXP, 1));
  INTEGER(NGSIZE)[0] = ngsize;
  
  PROTECT(RET = allocVector(VECSXP, 4));
  PROTECT(RET_NAMES = allocVector(STRSXP, 4));
  
  SET_VECTOR_ELT(RET, 0, str_ptr);
  SET_VECTOR_ELT(RET, 1, wl_ptr);
  SET_VECTOR_ELT(RET, 2, ng_ptr);
  SET_VECTOR_ELT(RET, 3, NGSIZE);
  
  SET_STRING_ELT(RET_NAMES, 0, mkChar("str_ptr"));
  SET_STRING_ELT(RET_NAMES, 1, mkChar("wl_ptr"));
  SET_STRING_ELT(RET_NAMES, 2, mkChar("ng_ptr"));
  SET_STRING_ELT(RET_NAMES, 3, mkChar("ngsize"));
  
  setAttrib(RET, R_NamesSymbol, RET_NAMES);
  
  UNPROTECT(6);
  return RET;
}


