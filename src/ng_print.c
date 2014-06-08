#include <R.h>
#include <Rinternals.h>
#include "ngram/src/print.h"


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
  
  Rprintf("%c", '\n');
  
  while(nwl)
  {
    print_word(nwl->word.word);
    Rprintf("{%d} | ", nwl->word.count);
    nwl = nwl->next;
  }
  
  Rprintf("%c", '\n');
  Rprintf("%c", '\n');
  
/*  free_list(ng->words);*/
/*  free_list(ng->nextword);*/
}

