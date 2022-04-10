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


#ifndef NGRAM_HASH_H
#define NGRAM_HASH_H

#include <stdint.h>

#include "process.h"
#include "lex.h"

tok_t get_token(wordlist_t *word, const int num);
tok_t get_token_str(const char *s, const int num);


#define INITIAL_HASHTAB_SIZE 512

typedef struct val_list_s{
	struct val_list_s *next;
	void *value;
}val_list_t;

typedef struct var_t{
	tok_t rawhash;
	val_list_t *vlist; // list of collisions for this slot
}var_t;

struct hashtable{
	int filled; // filled slots
	int size; // num slots
	int n_vals; // total items including collisions
	var_t **tab;
};

int init_hashtable(struct hashtable *tab, int initial_size);

//int get_hashtable_index(tok_t k, struct hashtable *htab);
int update_hashtable_value_ngram(ngram_t *ng, struct hashtable *htab);
ngram_t* get_hashtable_value_ngram(ngram_t *ng, struct hashtable *htab);
void free_hashtable_data(struct hashtable *htab, void (*freedata)(void*));

int word_cmp(word_t *a, word_t *b); // compare for sort
int word_eq(word_t *a, word_t *b); // quickly test equality; nonzero if equal
int ngram_eq(void *a, void *b); // same, but for ngrams

#endif
