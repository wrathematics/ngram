#ifndef NGRAM_GENERATE_H
#define NGRAM_GENERATE_H


typedef struct ngram_opts_t
{
  int n;
  int genlen;
  char *infile;
  char *outfile;
} ngram_opts_t;

int ngram_gen(rng_state_t *rs, ngramlist_t *ngl, int genlen, char **ret);


#endif
