#ifndef NGRAM_WORDCMP_H
#define NGRAM_WORDCMP_H

#include <string.h>
#include "lex.h"

#define TRUE 1
#define FALSE 0

char *word_to_string(word_t *word);
int wordcmp(word_t *word1, word_t *word2);
int wordstrcmp(word_t *word, char *str, int strlen);

#endif
