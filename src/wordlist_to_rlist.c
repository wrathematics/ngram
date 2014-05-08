#include "ngram.h"

#if 0
SEXP ngramlist_to_Rlist(ngram_t *ng, int ngsize)
{
  SEXP R_list;
  
  for(i=0; i<ngsize; i++)
    print_ngram(ng + i);
  
  free_wordlist(wl);
  
  return R_list;
}
#endif
