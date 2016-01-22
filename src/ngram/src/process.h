/*  Copyright (c) 2014, Heckendorf and Schmidt
    2015 Schmidt
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


#ifndef NGRAM_PROCESS_H
#define NGRAM_PROCESS_H

#include "lex.h"

typedef struct nextword_t{
	word_t *word; // pointer to the word
	int count; // number of times this word was seen
} nextword_t;

typedef struct nextwordlist_t{
	struct nextwordlist_t *next; // pointer to the next element in the list or NULL
	nextword_t word; // the data for this list element
} nextwordlist_t;

typedef struct ngram_t{
	tok_t tok; // complete ngram hash
	wordlist_t *words; // list of words in the ngram
	nextwordlist_t *nextword; // list of possible next-words and their counts for this ngram
	int count; // number of occurrences of ngram
} ngram_t;

typedef struct ngramlist_t{
	ngram_t *ng;
	int ngsize;
	int n;
} ngramlist_t;


void free_ngl(ngramlist_t *ngl);
ngramlist_t* process(sentencelist_t *wordtok, int n);

#endif
