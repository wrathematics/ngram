#include "ngram.h"


SEXP test(SEXP R_str)
{
  //const char *str="a bird is a dog man, a bird";
  //const int n=1;
  const char *str = CHARPT(R_str, 0);
  const int n=2;
  wordlist_t *wl;
  ngram_t *ng;
  int ngsize;
  int i;
  
  
  wl = lex(str, strlen(str));
  ng = process(wl, n, &ngsize);
  
  for(i=0; i<ngsize; i++)
    print_ngram(ng + i);
  
  free_wordlist(wl);
  
  return R_NilValue;
}
