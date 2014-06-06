#include "print.h"
#include "process.h"
#include "strings.h"
#include "rand/rand.h"


int simple_example()
{
  const char *str = "A A A B A B B A";
  const int n = 2;
  wordlist_t *wl;
  ngram_t *ng;
  int ngsize;
  int i;
  
  wl = lex(str, strlen(str));
  ng = process(wl, n, &ngsize);
  
  if(ng == NULL)
    printf("No ngrams\n");
  else
  {
    for(i=0; i<ngsize; i++)
      print_ngram(ng+i);
  }
  
  free_wordlist(wl);
  
  return 0;
}



int gen_example()
{
  const int n = 2;
  const char *str = "A A A B A B B A C";
  wordlist_t *wl;
  ngram_t *ng;
  int ngsize;
  wl = lex(str, strlen(str));
  ng = process(wl, n, &ngsize);
  
  rng_state_t rs;
  const int seed = 1234;
  rng_prepare(&rs);
  rng_set_type(&rs, RNG_TYPE_MT);
  rng_init(&rs, seed);
  
  const int genlen = 20;
  char *ret;
  int retlen;
  
  retlen = ngram_gen(n, &rs, ng, ngsize, genlen, &ret);
  
  printf("%s\n", ret);
  free(ret);
  
  return 0;
}



int main()
{
  simple_example();
  
  gen_example();
  
  return 0;
}


