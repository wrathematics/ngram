#include "../src/ngram.h"


int main(int argc, char **argv)
{
  int n = 2;
  const char *str = "ABC D EF GHI J K LMNO";
  
  int num_commonest = 2;
  
  wordlist_t *wl;
  ngramlist_t *ngl;
  wl = lex(str, strlen(str));
  ngl = process(wl, n);
  
  ngram_summary(ngl, num_commonest);
  
  return 0;
}


