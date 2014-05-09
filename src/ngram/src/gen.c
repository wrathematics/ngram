#include "process.h"
#include "hash.h"
#include "print.h"
#include "wordcmp.h"

#define OVERALLOC 25


// genlen = #words
char* gen(ngram_t *ng, int ngsize, int genlen)
{
  char *ret;
  int i, n;
  wordlist_t *wl = ng->words;
  nextwordlist_t *nwl = ng->nextword;
  
  ret = malloc(OVERALLOC * genlen * sizeof(*x));
  
  
  return 0;
}

