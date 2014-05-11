#include "process.h"
#include "hash.h"
#include "print.h"
#include "wordcmp.h"

#include "rand/rand.h"

#include <stdbool.h>


#define OVERALLOC 20


// genlen = #words
char* gen(rng_state_t *rs, ngram_t *ng, int ngsize, int genlen)
{
  char *ret;
  int i, n;
  int ng_ind;
  bool init = true;
  wordlist_t *wl = ng->words;
  nextwordlist_t *nwl = ng->nextword;
  
/*  ret = malloc(OVERALLOC * genlen * sizeof(*ret));*/
  
  while (genlen)
  {
    while (init)
    {
      ng_ind = sample(rs, 0, ngsize-1); 
      printf("%d\n", ng_ind);
      init = false;
    }
    
    print_ngram(& ng[ng_ind]);
    break;
    genlen--;
  }
  
  
  return 0;
}



