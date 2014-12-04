#ifndef __RPKG_NGRAM_H__
#define __RPKG_NGRAM_H__


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
uint32_t mix_96(uint32_t a, uint32_t b, uint32_t c);
int ngram_wordcount(const char *str, const char sep);


#endif
