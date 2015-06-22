/*  Copyright (c) 2014-2015, Heckendorf and Schmidt
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


#include <string.h>

#include "process.h"

static void *vptr;


void free_ngl(ngramlist_t *ngl)
{
  int i;
  
  for (i=0; i<ngl->ngsize; i++)
  {
    free_list(ngl->ng[i].words);
    free_list(ngl->ng[i].nextword);
  }
  
  free(ngl->ng);
  free(ngl);
}


static int cmp_ngram(const void *a, const void *b){
  ngram_t **na = (ngram_t**)a;
  ngram_t **nb = (ngram_t**)b;

  if((*na)->tok<(*nb)->tok)
    return -1;
  else if((*na)->tok>(*nb)->tok)
    return 1;
  else{
    if((*na)->nextword->word.word == NULL)
      return -1;
    else if((*nb)->nextword->word.word == NULL)
      return 1;
    else if((*na)->nextword->word.word->tok<(*nb)->nextword->word.word->tok)
      return -1;
    else if((*na)->nextword->word.word->tok>(*nb)->nextword->word.word->tok)
      return -1;
  }
  return 0;
}



ngramlist_t* process(wordlist_t *words, int n)
{
  int i, j, js, len, ngsize;
  wordlist_t *p, *q, *nw;
  ngram_t *ng, *tmp, **sorted;
  ngramlist_t *ngl;
  
  ngl = malloc(sizeof(ngramlist_t));
  ngl->ngsize = 0;
  
  if (n<1)
    return NULL;
  
  len = 0;
  p = words;
  while (p){
    len++;
    p = p->next;
  }
  len -= n-1;
  
  if (len<1)
    return NULL;
  
  // Hope this doesn't crash lol
  ng = malloc(sizeof(*ng)*len);
  ng->count = 0;
  
  tmp = malloc(sizeof(*tmp)*len);
  sorted = malloc(sizeof(*sorted)*len);
  
  nw = words;
  for (i = 1;i<len;i++){
    q = p = nw->next;
    tmp[i].tok = get_token(p,n);
    tmp[i].words = NULL;
    for (j = 0;j<n;j++){
      add_node(tmp[i].words);
      tmp[i].words->word = q->word;
      q = q->next;
    }
    tmp[i].nextword = NULL;
    add_node(tmp[i].nextword);
    tmp[i].nextword->word.word = nw->word;
    tmp[i].nextword->word.count = 0;
    
    sorted[i] = tmp+i;
    
    nw = nw->next;
  }
  
  q = p = words;
  tmp->tok = get_token(p,n);
  tmp->words = NULL;
  for (j = 0;j<n;j++){
    add_node(tmp->words);
    tmp->words->word = q->word;
    q = q->next;
  }
  tmp->nextword = NULL;
  add_node(tmp->nextword);
  tmp->nextword->word.word = NULL;
  tmp->nextword->word.count = 0;
  sorted[0] = tmp;
  
  qsort(sorted,len,sizeof(*sorted),cmp_ngram);
  
  ngsize = 0;
  for (i = 0;i<len;i = j) {
    js = i;
    for (j = i+1;j<len && sorted[j]->tok == sorted[i]->tok;j++){
      /* This may be a problem if we start working with more than one string (multiple NULLs) */
      if (sorted[js]->nextword->word.word != NULL && sorted[j]->nextword->word.word != NULL && sorted[j]->nextword->word.word->tok == sorted[js]->nextword->word.word->tok)
        sorted[js]->nextword->word.count++;
      else {
        sorted[js]->nextword->word.count++;
        add_node(sorted[js]->nextword);
        sorted[js]->nextword->word.count = 1;
        sorted[js]->nextword->word.word = sorted[j]->nextword->word.word;
      }
      free_list(sorted[j]->words);
      free_list(sorted[j]->nextword);
    }
    if (j == i+1)
      sorted[i]->nextword->word.count = 1;
    
    ng[ngsize].count = j-i;
    ng[ngsize].words = sorted[i]->words;
    ng[ngsize].nextword = sorted[i]->nextword;
    ng[ngsize].tok = sorted[i]->tok;
    ngsize++;
  }
  
  free(sorted);
  free(tmp);
  
  ngl->ng = ng;
  ngl->ngsize = ngsize;
  ngl->n = n;
  
  return ngl;
}


