// Copyright 2014, Heckendorf and Schmidt

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
  ngl = vptr;
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
/*  if( = NULL)*/
/*    exit(1);*/
  tmp = malloc(sizeof(*tmp)*len);
/*  if(() == NULL)*/
/*    exit(1);*/
  sorted = malloc(sizeof(*sorted)*len);
/*  if(() == NULL)*/
/*    exit(1);*/

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


