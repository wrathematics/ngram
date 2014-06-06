#ifndef __NGRAM_H__
#define __NGRAM_H__


#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "ngram/src/hash.h"
#include "ngram/src/lex.h"
#include "ngram/src/process.h"
#include "ngram/src/print.h"
#include "ngram/src/wordcmp.h"
#include "ngram/src/rand/rand.h"

// External pointer shorthand
#define newRptr(ptr,Rptr,fin) PROTECT(Rptr = R_MakeExternalPtr(ptr, R_NilValue, R_NilValue));R_RegisterCFinalizerEx(Rptr, fin, TRUE)
#define getRptr(ptr) R_ExternalPtrAddr(ptr);

// Misc R shorthand
#define CHARPT(x,i)	((char*)CHAR(STRING_ELT(x,i)))
#define INT(x) INTEGER(x)[0]

// ngram lib prototypes
int ngram_gen(const int n, rng_state_t *rs, ngram_t *ng, int ngsize, int genlen, char **ret);
int mix_96(int a, int b, int c);
int ngram_wordcount(const char *str, const char sep);


#endif
