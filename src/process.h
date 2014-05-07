#ifndef NGRAM_PROCESS_H
#define NGRAM_PROCESS_H

#include "lex.h"

typedef struct nextword_t{
	word_t *word;
	int count;
}nextword_t;

typedef struct nextwordlist_t{
	struct nextwordlist_t *next;
	nextword_t word;
}nextwordlist_t;

typedef struct ngram_t{
	tok_t tok;
	wordlist_t *words;
	nextwordlist_t *nextword;
}ngram_t;

typedef struct ngramlist_t{
	struct ngramlist_t *next;
	ngram_t ngram;
}ngramlist_t;

ngram_t* process(wordlist_t *words, int n, int *size);

#endif
