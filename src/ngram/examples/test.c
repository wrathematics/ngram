#include "../src/print.h"
#include "../src/process.h"
#include "../src/summary.h"


int main(int argc, char **argv)
{
  printf("asdf");
  int n = 3;
  /*  const char *str = "A A A B A B B A";*/
  const char *str = "ABC D EF GHI J K LMNO";
  
  int num_commonest = 2;
  
  wordlist_t *wl;
  ngram_t *ng;
  int ngsize;
  wl = lex(str, strlen(str));
  ng = process(wl, n, &ngsize);
  
  ngram_summary(n, ng, ngsize, num_commonest);
  
  return 0;
}


