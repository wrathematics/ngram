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
wordlist_t* lex(const char *s, const int len);

#endif
