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


SEXP ng_extract_ngrams(SEXP ng_ptr, SEXP ngsize_)
{
  int i, j, len;
  char *buf;
  ngramlist_t *ngl = (ngramlist_t *) getRptr(ng_ptr);
  ngram_t *ng = ngl->ng;
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
    
    buf = malloc(len * sizeof(*buf));
    
    for (j=0; j<len; j++)
      buf[j] = ng[i].words->word->s[j];
    
    SET_STRING_ELT(RET, i, mkCharLen(buf, len));
    
    
    free(buf);
  }
  
  UNPROTECT(1);
  return RET;
}



// huge broken mess
#if 0

// take lex return
// sort by tok and iterate over the list skipping duplicates
SEXP ng_extract_words(SEXP ng_ptr, SEXP ngsize_)
{
  int i, j, k;
  int len, retlen;
  char *buf;
  ngram_t *ng = (ngram_t *) getRptr(ng_ptr);
  const int ngsize = INTEGER(ngsize_)[0];
  wordlist_t *wl;
  
  SEXP RET;
  
  // Count # words
  
  retlen = 2;
  
  PROTECT(RET = allocVector(STRSXP, retlen));
  
  // Convert them
  k = 0;
  
  for(i=0; i<ngsize; i++)
  {
    wl = ng[i].words;
    
    while(wl)
    {
      print_word(ng[i].words->word);
    }
    
    if(ng[i].words->word == NULL)
    {
/*        SET_STRING_ELT(RET, i, mkChar("<NA>"));*/
      goto nextcycle;
    }
    
    len = ng[i].words->word->len;
    buf = malloc(len * sizeof(buf));
    
    for (j=0; j<len; j++)
      buf[j] = ng[i].words->word->s[j];
    
    SET_STRING_ELT(RET, k, mkCharLen(buf, len));
    
    free(buf);
    
    
    nextcycle:
      k++;
      wl = wl->next;
  }
  
  UNPROTECT(1);
  return RET;
}
#endif



SEXP ng_extract_str(SEXP str_ptr, SEXP R_strlen)
{
  SEXP RET;
  char *str = (char *) getRptr(str_ptr);
  
  PROTECT(RET = allocVector(STRSXP, 1));
  
  SET_STRING_ELT(RET, 0, mkCharLen(str, INTEGER(R_strlen)[0]));
  
  UNPROTECT(1);
  return RET;
}


