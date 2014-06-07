#include "print.h"
#include "process.h"
#include "strings.h"
#include "rand/rand.h"


#if 0
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
  const int n = 3;
/*  const char *str = "A A A B A B B A";*/
/*  const int genlen = 20;*/
  
  const char *str = "A B C";
  const int genlen = 10;
  
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
  
  
  char *ret;
  int retlen;
  
  retlen = ngram_gen(n, &rs, ng, ngsize, genlen, &ret);
  
  printf("%s\n", ret);
  free(ret);
  
  return 0;
}



int main()
{
/*  simple_example();*/
  
  gen_example();
  
  return 0;
}
#endif


int ngram_gen(const int n, rng_state_t *rs, ngram_t *ng, int ngsize, int genlen, char **ret);


int main_gen(const int n, const char *str, const int genlen, const int seed)
{
  wordlist_t *wl;
  ngram_t *ng;
  int ngsize;
  wl = lex(str, strlen(str));
  ng = process(wl, n, &ngsize);
  
  rng_state_t rs;
  rng_prepare(&rs);
  rng_set_type(&rs, RNG_TYPE_MT);
  rng_init(&rs, seed);
  
  char *ret;
  int retlen;
  
  retlen = ngram_gen(n, &rs, ng, ngsize, genlen, &ret);
  
  printf("%s\n", ret);
  free(ret);
  
  return 0;
}







int main(int argc, char *argv[])
{
  int n = 3;
  /*  const char *str = "A A A B A B B A";*/
/*  const int genlen = 20;*/
  const char *str = "A B C";
  const int genlen = 10;
  const uint32_t seed = 1234;
  
  main_gen(n, str, genlen, seed);
  
  return 0;
}






