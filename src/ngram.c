#include "ngram.h"

void ctest()
{
  char *str="tofu eats beans eats beans tofu eats rice nice";
  int n=2;
/*  const char *str = CHARPT(R_str, 0);*/
/*  const int n = INTEGER(n_)[0];*/
  wordlist_t *wl;
  ngram_t *ng;
  int ngsize;
  int i;
  
  printf("%s\n", str);
  
  wl = lex(str, strlen(str));
/*  wl = lex(str, LENGTH(R_str));*/
  ng = process(wl, n, &ngsize);
  
  for(i=0; i<ngsize; i++)
    print_ngram(ng + i);
  
  free_wordlist(wl);
}

SEXP test()
{
  ctest();
  
  return R_NilValue;
}


