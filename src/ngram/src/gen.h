#ifndef NGRAM_GENERATE_H
#define NGRAM_GENERATE_H


typedef struct ngram_opts_t
{
  int n;
  int genlen;
  char *infile;
  char *outfile;
} ngram_opts_t;


#endif
