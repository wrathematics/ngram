// Copyright 2014, Schmidt

#include <stdio.h>
#include <stdlib.h>

#include "lex.h"
#include "process.h"
#include "hash.h"
#include "print.h"


// sort in reverse order
static int compare(const void *a, const void *b)
{
  int x = *(const int *)a;
  int y = *(const int *)b;
  
  if (x == y)
    return 0;
  else
    return (x<y)?1:-1;
}



static inline int ngram_nchar(const int n, const ngram_t *ng, int i)
{
  int j;
  int nch = 0;
  
  for (j=0; j<n; i++)
    nch += ng[i].words->word->len;
  
  return nch;
}



static inline void iswap(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}



void ngram_summary_ptrs(const int n, const ngram_t *ng, const int ngsize, int *longest, int *shortest, int *commonest, int num_commonest)
{
  int i, i_nch, tmp;
  int longest_nch, shortest_nch;
  
  longest = 0;
  shortest = 0;
  
  longest_nch = ngram_nchar(n, ng, 0);
  shortest_nch = longest_nch;
  
  
  for (i=0; i<num_commonest; i++)
    commonest[i] = i;
  
  for (i=1; i<ngsize; i++)
  {
    i_nch = ngram_nchar(n, ng, i);
    
    // longest
    if (i_nch > longest_nch)
    {
      longest_nch = i_nch;
      *longest = i;
    }
    
    //shortest
    if (i_nch < shortest_nch)
    {
      shortest_nch = i_nch;
      *shortest = i;
    }
    
    // top n
    /*
    if (i >= num_commonest)
    {
      
      qsort(commonest, num_commonest, sizeof(int), compare);
      
    }
    */
  }
}



void ngram_summary_printer(const int n, const ngram_t *ng, const int ngsize, int *longest, int *shortest, int *commonest, int num_commonest)
{
  printf("Longest:\t");
  print_ngram_nonext(ng + *longest);
  putchar('\n');
  
  printf("Shortest:\t");
/*  print_ngram_nonext(ng + shortest);*/
  putchar('n');
}



void ngram_summary(const int n, const ngram_t *ng, const int ngsize, int num_commonest)
{
  int longest, shortest;
  int *commonest = malloc(num_commonest * sizeof(*commonest));
  
  ngram_summary_ptrs(n, ng, ngsize, &longest, &shortest, commonest, num_commonest);
  
  
  
  free(commonest);
}



