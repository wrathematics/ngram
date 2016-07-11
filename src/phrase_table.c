/*  Copyright (c) 2015, Schmidt
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

SEXP R_ng_get_phrasetable(SEXP ng_ptr, SEXP ngsize_)
{
  int i, j, len;
  char *buf = NULL;
  ngramlist_t *ngl = (ngramlist_t *) getRptr(ng_ptr);
  ngram_t *ng = ngl->ng;
  const int ngsize = INTEGER(ngsize_)[0];
  wordlist_t *wl;
  int tot = 0;
  int bufsize;
  
  SEXP RET, RETNAMES;
  SEXP NGRAMS, FREQ, PROP;
  PROTECT(NGRAMS = allocVector(STRSXP, ngsize));
  PROTECT(FREQ = allocVector(INTSXP, ngsize));
  PROTECT(PROP = allocVector(REALSXP, ngsize));
  int *freq = INTEGER(FREQ);
  double *prop = REAL(PROP);
  
  for (i=0; i<ngsize; i++)
  {
    freq[i] = 0;
    len = 0;
    wl = ng[i].words;
    
    while (wl)
    {
      len += wl->word->len;
      len++; // spaces
      wl = wl->next;
    }
    
    // mkCharLen doesn't require NUL terminated strings but it's probably
    // better/faster to overallocate by 1 and simplify the memcpy loop
    if (buf == NULL || bufsize < (len+1))
    {
      if (buf)
        free(buf);
      
      bufsize = len+1;
      buf = malloc(bufsize * sizeof(*buf));
      if(buf == NULL)
          error("out of memory");
    }
    
    
    wl = ng[i].words;
    for (j=0; wl; wl = wl->next)
    {
      memcpy(buf+j,wl->word->s,wl->word->len);
      j += wl->word->len;
      buf[j++] = ' '; // XXX funky output here if ' ' is valid in words, oh well
    }
    // we could "buf[j-1] = 0;" here to be safe but: ~no rice, no life~
    
    SET_STRING_ELT(NGRAMS, i, mkCharLen(buf,len));
    
    freq[i] = ng[i].count;
    tot += ng[i].count;
  }
  
  free(buf);
  
  
  for (i=0; i<ngsize; i++)
  {
    prop[i] = (double) freq[i]/tot;
  }
  
  PROTECT(RET = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(RET, 0, NGRAMS);
  SET_VECTOR_ELT(RET, 1, FREQ);
  SET_VECTOR_ELT(RET, 2, PROP);
  
  PROTECT(RETNAMES = allocVector(STRSXP, 3));
  SET_STRING_ELT(RETNAMES, 0, mkChar("ngrams"));
  SET_STRING_ELT(RETNAMES, 1, mkChar("freq"));
  SET_STRING_ELT(RETNAMES, 2, mkChar("prop"));
  setAttrib(RET, R_NamesSymbol, RETNAMES);
  
  UNPROTECT(5);
  return RET;
}
