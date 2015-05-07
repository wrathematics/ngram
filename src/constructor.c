/*  Copyright (c) 2014, Schmidt
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


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
  const size_t len = INTEGER(R_str_len)[0] +1 ;
  
  SEXP RET, RET_NAMES, NGSIZE;
  SEXP str_ptr, wl_ptr, ngl_ptr;
  
  
  str = malloc(len * sizeof(*str));
  strncpy(str, CHARPT(R_str, 0), len);
  
  wl = lex(str, len-1);
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


