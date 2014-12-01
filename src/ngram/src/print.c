// Copyright 2014, Heckendorf and Schmidt

#include "print.h"


void print_word(word_t *word)
{
  int i;
  
  if(word == NULL)
  {
    printf("NULL ");
    return;
  }
  
  for(i=0; i<word->len; i++)
    putchar(word->s[i]);
  
  putchar(' ');
}



void print_ngram_nonext(ngram_t *ng)
{
  wordlist_t *wl = ng->words;
  
  while(wl)
  {
    print_word(wl->word);
    wl = wl->next;
  }
  
  putchar('\n');
}



void print_ngram(ngram_t *ng)
{
  nextwordlist_t *nwl = ng->nextword;
  
  print_ngram_nonext(ng);
  
  while(nwl)
  {
    print_word(nwl->word.word);
    printf("{%d} | ", nwl->word.count);
    nwl = nwl->next;
  }
  
  putchar('\n');
  putchar('\n');
}

