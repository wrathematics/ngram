#ifndef NGRAM_PROCESS_H
#define NGRAM_PROCESS_H

#include "lex.h"

typedef struct nextword_t{
	word_t *word; /* pointer to the word */
	int count; /* number of times this word was seen */
} nextword_t;

typedef struct nextwordlist_t{
	struct nextwordlist_t *next; /* pointer to the next element in the list or NULL */
	nextword_t word; /* the data for this list element */
} nextwordlist_t;

typedef struct ngram_t{
	tok_t tok; /* complete ngram hash */
	wordlist_t *words; /* list of words in the ngram */
	nextwordlist_t *nextword; /* list of possible next-words and their counts for this ngram */
} ngram_t;

typedef struct ngramlist_t{
	ngram_t *ng;
	int ngsize;
	int n;
} ngramlist_t;


void free_ngl(ngramlist_t *ngl);
ngramlist_t* process(wordlist_t *words, int n);

#endif
