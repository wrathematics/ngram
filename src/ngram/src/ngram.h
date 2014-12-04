#ifndef NGRAM_GENERATE_H
#define NGRAM_GENERATE_H


typedef struct ngram_opts_t
{
  int n;
  int genlen;
  char *infile;
  char *outfile;
} ngram_opts_t;

#include "gen.h"
#include "hash.h"
#include "lex.h"
#include "print.h"
#include "process.h"
#include "sorts.h"
#include "summary.h"
#include "wordcmp.h"

#include "rand/platform.h"
#include "rand/rand.h"
#include "rand/rng_interface.h"


#endif
