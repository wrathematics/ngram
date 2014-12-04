/*  Copyright (c) 2014, Heckendorf
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


#ifndef NGRAM_LEX_H
#define NGRAM_LEX_H


#include <stdlib.h>
#include <stdint.h>

//#define add_node(l) {vptr=l;if((l=malloc(sizeof(*l)))==NULL)exit(1);l->next=vptr;}
#define add_node(l) {vptr=l;l=malloc(sizeof(*l));l->next=vptr;}
#define free_list(l) {while(l){vptr=l->next;free(l);l=vptr;}}

typedef uint32_t tok_t;

typedef struct word_t{
	const char *s; /* a pointer to the start of the word */
	int len; /* number of characters in the word */
	tok_t tok; /* word hash */
} word_t;

typedef struct wordlist_t{
	struct wordlist_t *next; /* pointer to the next element in the list or NULL */
	word_t *word; /* pointer to the word for this element in the list */
} wordlist_t;

#include "hash.h"

void free_wordlist(wordlist_t *wl);
void free_wordlist_keepwords(wordlist_t *wl);
wordlist_t* lex(const char *s, const int len);


#endif
