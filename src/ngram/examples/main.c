#include "../src/ngram.h"


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


int ngram_gen(rng_state_t *rs, ngramlist_t *ngl, int genlen, char **ret);


int main_gen(const int n, const char *str, const int genlen, const int seed)
{
  wordlist_t *wl;
  ngramlist_t *ngl;
  int ngsize;
  wl = lex(str, strlen(str));
  ngl = process(wl, n);
  
  rng_state_t rs;
  rng_prepare(&rs);
  rng_set_type(&rs, RNG_TYPE_MT);
  rng_init(&rs, seed);
  
  char *ret;
  int retlen;
  
  retlen = ngram_gen(&rs, ngl, genlen, &ret);
  
  printf("%s\n", ret);
  free(ret);
  
  return 0;
}



void ngram_set_main_flags(ngram_opts_t *opts, int argc, char **argv)
{
  int i;
  
  opts->n = 3;
  opts->genlen = 10;
  opts->infile = "";
  opts->outfile = "";
  
  for (i=1; i<argc; i++)
  {
    if (0 == strcmp(argv[i], "--n"))
      opts->n = (int)(argv[i+1][0] - '0');
    else if (0 == strcmp(argv[i], "--genlen"))
      opts->genlen = (int)(argv[i+1][0] - '0');
    else if (0 == strcmp(argv[i], "--infile"))
      opts->infile = argv[i+1];
    else if (0 == strcmp(argv[i], "--outfile"))
      opts->outfile = argv[i+1];
  }
}



int main(int argc, char **argv)
{
  int n = 3;
  /*  const char *str = "A A A B A B B A";*/
/*  const int genlen = 20;*/
  const char *str = "A B A C A B B";
  const int genlen = 10;
  const uint32_t seed = 1234;
  
  ngram_opts_t opts;
  
  ngram_set_main_flags(&opts, argc, argv);
  
  main_gen(opts.n, str, opts.genlen, seed);
  
  return 0;
}


