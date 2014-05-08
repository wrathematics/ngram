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

// Obtain character pointers
#define CHARPT(x,i)	((char*)CHAR(STRING_ELT(x,i)))


#endif
