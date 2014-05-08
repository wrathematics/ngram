#ifndef NGRAM_PRINT_H
#define NGRAM_PRINT_H

#include <stdio.h>
#include <string.h>

#include "hash.h"
#include "lex.h"
#include "process.h"

void print_word(word_t *word);
void print_ngram(ngram_t *ng);

#endif
