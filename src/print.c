/*  Copyright (c) 2014-2015, Schmidt
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

void print_word(word_t *word)
{
  int i;
  
  if(word == NULL)
  {
    Rprintf("NULL ");
    return;
  }
  
  for(i=0; i<word->len; i++)
    Rprintf("%c", word->s[i]);
  
  Rprintf("%c", ' ');
}



void print_ngram(ngram_t *ng)
{
  wordlist_t *wl = ng->words;
  nextwordlist_t *nwl = ng->nextword;
  
  while(wl)
  {
    print_word(wl->word);
    wl = wl->next;
  }
  
  Rprintf("| %d %c", ng->count, '\n');
  
  while(nwl)
  {
    print_word(nwl->word.word);
    Rprintf("{%d} | ", nwl->word.count);
    nwl = nwl->next;
  }
  
  Rprintf("%c", '\n');
  Rprintf("%c", '\n');
}



#define TRUNCSIZE 5
SEXP R_ng_print(SEXP ng_ptr, SEXP ngsize_, SEXP truncated)
{
  int i;
  ngramlist_t *ngl = (ngramlist_t *) getRptr(ng_ptr);
  const int ngsize = INTEGER(ngsize_)[0];
  int maxiter;
  
  maxiter = INTEGER(truncated)[0] ? MIN(TRUNCSIZE,ngsize) : ngsize;
  
  
  for(i=0; i<maxiter; i++)
    print_ngram(ngl->ng + i);
  
  if (INTEGER(truncated)[0] && TRUNCSIZE < ngsize)
    Rprintf("[[ ... results truncated ... ]]\n");
  
  return R_NilValue;
}
