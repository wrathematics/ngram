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

// External pointer shorthand
#define newRptr(ptr,Rptr,fin) PROTECT(Rptr = R_MakeExternalPtr(ptr, R_NilValue, R_NilValue));R_RegisterCFinalizerEx(Rptr, fin, TRUE)
#define getRptr(ptr) R_ExternalPtrAddr(ptr);

// Obtain character pointers
#define CHARPT(x,i)	((char*)CHAR(STRING_ELT(x,i)))


#endif
