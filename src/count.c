/*  Copyright (c) 2014-2015, Schmidt
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "ngram.h"


SEXP R_ngram_wordcount(SEXP str, SEXP sep)
{
  SEXP ret;
  PROTECT(ret = allocVector(INTSXP, 1));
  
  INT(ret) = ngram_wordcount(CHARPT(str, 0), CHARPT(sep, 0)[0]);
  
  UNPROTECT(1);
  return ret;
}




#define LEN1INTVEC(Rname,value) \
  PROTECT(Rname = allocVector(INTSXP, 1)); \
  INTEGER(Rname)[0] = value

#define MIN(a,b) (a<b?a:b)

SEXP R_stringsummary(SEXP string, SEXP wordlen_max)
{
  SEXP ret, ret_names;
  SEXP Rchars, Rletters, Rwhitespace, Rpunctuation, Rdigits;
  SEXP Rwords, Rsentences, Rlines;
  
  SEXP wordlens;
  PROTECT(wordlens = allocVector(INTSXP, INT(wordlen_max)));
  
  ngram_summary_t ngsum;
  ngram_stringsummary(CHARPT(string, 0), INT(wordlen_max), &ngsum);
  
  for (int i=0; i<INT(wordlen_max); i++)
    INTEGER(wordlens)[i] = ngsum.wordlens[i];
  
  LEN1INTVEC(Rchars, ngsum.chars);
  LEN1INTVEC(Rletters, ngsum.letters);
  LEN1INTVEC(Rwhitespace, ngsum.whitespace);
  LEN1INTVEC(Rpunctuation, ngsum.punctuation);
  LEN1INTVEC(Rdigits, ngsum.digits);
  LEN1INTVEC(Rwords, ngsum.words);
  LEN1INTVEC(Rsentences, ngsum.sentences);
  LEN1INTVEC(Rlines, ngsum.lines);
  
  PROTECT(ret = allocVector(VECSXP, 9));
  SET_VECTOR_ELT(ret, 0, Rchars);
  SET_VECTOR_ELT(ret, 1, Rletters);
  SET_VECTOR_ELT(ret, 2, Rwhitespace);
  SET_VECTOR_ELT(ret, 3, Rpunctuation);
  SET_VECTOR_ELT(ret, 4, Rdigits);
  SET_VECTOR_ELT(ret, 5, Rwords);
  SET_VECTOR_ELT(ret, 6, Rsentences);
  SET_VECTOR_ELT(ret, 7, Rlines);
  SET_VECTOR_ELT(ret, 8, wordlens);
  
  PROTECT(ret_names = allocVector(STRSXP, 9));
  SET_STRING_ELT(ret_names, 0, mkChar("chars"));
  SET_STRING_ELT(ret_names, 1, mkChar("letters"));
  SET_STRING_ELT(ret_names, 2, mkChar("whitespace"));
  SET_STRING_ELT(ret_names, 3, mkChar("punctuation"));
  SET_STRING_ELT(ret_names, 4, mkChar("digits"));
  SET_STRING_ELT(ret_names, 5, mkChar("words"));
  SET_STRING_ELT(ret_names, 6, mkChar("sentences"));
  SET_STRING_ELT(ret_names, 7, mkChar("lines"));
  SET_STRING_ELT(ret_names, 8, mkChar("wordlens"));
  setAttrib(ret, R_NamesSymbol, ret_names);
  
  free(ngsum.wordlens);
  
  UNPROTECT(11);
  return ret;
}


