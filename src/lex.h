#ifndef NGRAM_LEX_H
#define NGRAM_LEX_H

#include <stdlib.h>
#include <stdint.h>

#define add_node(l) {vptr=l;if((l=malloc(sizeof(*l)))==NULL)exit(1);l->next=vptr;}
#define free_list(l) {while(l){vptr=l->next;free(l);l=vptr;}}

typedef uint32_t tok_t;

typedef struct word_t{
	const char *s;
	int len;
	tok_t tok;
}word_t;

typedef struct wordlist_t{
	struct wordlist_t *next;
	word_t *word;
}wordlist_t;

#include "hash.h"

void free_wordlist(wordlist_t *wl);
wordlist_t* lex(const char *s, const int len);

#endif
