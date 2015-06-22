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


SEXP R_ng_get_phrasetable(SEXP ng_ptr, SEXP ngsize_)
{
  int i, j, len;
  char *buf;
  ngramlist_t *ngl = (ngramlist_t *) getRptr(ng_ptr);
  ngram_t *ng = ngl->ng;
  const int ngsize = INTEGER(ngsize_)[0];
  wordlist_t *wl;
  
  SEXP RET, RETNAMES;
  SEXP NGRAMS, FREQ, PROP;
  PROTECT(NGRAMS = allocVector(STRSXP, ngsize));
  PROTECT(FREQ = allocVector(INTSXP, ngsize));
  PROTECT(PROP = allocVector(REALSXP, ngsize));
  int *freq = INTEGER(freq);
  double *prop = REAL(PROP);
  
  for(i=0; i<ngsize; i++)
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
    
    len--; // apparently mkCharLen handles the NUL terminator for some reason
    
    buf = malloc(len * sizeof(*buf));
    
    for (j=0; j<len; j++)
      buf[j] = ng[i].words->word->s[j];
    
    SET_STRING_ELT(NGRAMS, i, mkCharLen(buf, len));
    
    
    free(buf);
  }
  
  UNPROTECT(1);
  return RET;
}
