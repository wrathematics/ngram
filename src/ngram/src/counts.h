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


#ifndef NGRAM_COUNTS_H
#define NGRAM_COUNTS_H


#define MIN(a,b) (a<b?a:b)
#define NOTNUL(x) (x[i] != '\0')

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "hash.h"
#include "lex.h"
#include "process.h"


typedef struct ngram_summary_t
{
  int chars;
  int letters;
  int whitespace;
  int punctuation;
  int digits;
  int words;
  int sentences;
  int lines;
  int *wordlens;
} ngram_summary_t;

int find_ngram_count(ngramlist_t *ng, tok_t tok);
int ngram_counts_maxind(ngram_t *ng, int ngsize);
int ngram_counts_total(ngram_t *ng, int ngsize);
int ngram_wordcount(const char *str, const char sep);
int ngram_stringsummary(char *str, const int wordlen_max, ngram_summary_t *ngsum);


#endif
