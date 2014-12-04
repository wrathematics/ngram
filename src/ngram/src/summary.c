// Copyright 2014, Schmidt

#include <stdio.h>
#include <stdlib.h>

#include "hash.h"
#include "lex.h"
#include "print.h"
#include "process.h"
#include "sorts.h"
#include "summary.h"


static inline int ngram_nchar(const int n, const ngram_t *ng, int i)
{
  int nch = 0;
  
  wordlist_t *wl = ng->words;
  
  while(wl)
  {
    nch += wl->word->len + 1; // for the space
    wl = wl->next;
  }
  
  nch--; // overcounted number of spaces by 1
  
  return nch;
}



static inline void iswap(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}



void ngram_summary_ptrs(const int n, const ngram_t *ng, const int ngsize, ngsummary_t *ngsummary)
{
  int i, i_nch, tmp;
  
  ngsummary->longest = 0;
  ngsummary->shortest = 0;
  
  ngsummary->longest_nch = ngram_nchar(n, ng, 0);
  ngsummary->shortest_nch = ngsummary->longest_nch;
  
  for (i=0; i<ngsummary->num_commonest; i++)
    ngsummary->commonest[i] = i;
  
  
  for (i=1; i<ngsize; i++)
  {
    i_nch = ngram_nchar(n, ng, i);
    
    // longest
    if (i_nch > ngsummary->longest_nch)
    {
      ngsummary->longest_nch = i_nch;
      ngsummary->longest = i;
    }
    
    //shortest
    if (i_nch < ngsummary->shortest_nch)
    {
      ngsummary->shortest_nch = i_nch;
      ngsummary->shortest = i;
    }
    
    // top n
/*    if (i >= ngsummary->num_commonest)*/
/*    {*/
/*      */
/*      ngram_sesort(ngsummary->num_commonest, int *y, ngsummary->commonest)*/
/*      */
/*    }*/
  }
}



static void ngram_summary_printer(const int n, ngram_t *ng, const int ngsize, ngsummary_t *ngsummary)
{
  printf("Longest:\t%d chars\n", ngsummary->longest_nch);
  print_ngram_nonext(ng + ngsummary->longest);
  
  printf("Shortest:\t%d chars\n", ngsummary->shortest_nch);
  print_ngram_nonext(ng + ngsummary->shortest);
}



void ngram_summary(ngramlist_t *ngl, int num_commonest)
{
  ngsummary_t ngsummary;
  ngsummary.num_commonest = num_commonest;
  int *commonest = malloc(num_commonest * sizeof(*commonest));
  ngsummary.commonest = commonest;
  
/*  if (num_commonest > n)*/
  
  ngram_summary_ptrs(ngl->n, ngl->ng, ngl->ngsize, &ngsummary);
  ngram_summary_printer(ngl->n, ngl->ng, ngl->ngsize, &ngsummary);
  
  free(commonest);
}


