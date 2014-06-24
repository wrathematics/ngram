// Copyright 2014, Heckendorf

#include "hash.h"
#include "lex.h"

tok_t get_token(wordlist_t *word, const int num){
	tok_t ret;
	int i,j;

	ret=0;
	for(i=0;i<num;i++){
		for(j=0;j<word->word->len;j++){
			ret += word->word->s[j];
			ret += (ret<<10);
			ret ^= (ret>>6);
		}
		word=word->next;
	}
	ret += (ret<<3);
	ret ^= (ret>>11);
	ret += (ret<<15);

	return ret;
}

