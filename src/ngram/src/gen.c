#include "process.h"
#include "hash.h"
#include "print.h"
#include "wordcmp.h"


#define OVERALLOC 20

static void *vptr;

int gen(ngram_t *ng, char **x, int len)
{
  int i, test=0;
  wordlist_t *wl = ng->words;
  nextwordlist_t *nwl = ng->nextword;
  
  *x = malloc(OVERALLOC * len * sizeof(*x));
  
  for (i=0; i<len; i++)
  {
    while(wl)
    {
/*      test = wordcmp(word, char *str, int strlen);*/
      if (test == TRUE)
        break;
      
      wl = wl->next;
    }
    
    putchar('\n');
    
    while(nwl)
    {
/*      print_word(nwl->word.word);*/
/*      printf("{%d} | ",nwl->word.count);*/
      nwl = nwl->next;
    }
  }
  
  
  free_list(ng->words);
  free_list(ng->nextword);
  
  return 0;
}

