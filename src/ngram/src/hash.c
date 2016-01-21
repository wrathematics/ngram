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


#include "hash.h"
#include "lex.h"

#define add_hash_char(x,y) do \
							{y += x;\
							 y += (y<<10);\
							 y ^= (y>>6);}while(0)

#define hash_finalize(y) do \
						 {ret += (ret<<3);\
						  ret ^= (ret>>11);\
						  ret += (ret<<15);}while(0)

tok_t get_token(wordlist_t *word, const int num){
	tok_t ret;
	int i,j;

	ret=0;
	for(i=0;i<num;i++){
		for(j=0;j<word->word->len;j++){
			add_hash_char(word->word->s[j],ret);
		}
		word=word->next;
	}
	hash_finalize(ret);

	return ret;
}

/* Get the hash for a string, assuming NULL word sep. */
tok_t get_token_str(const char *s, const int num){
	int i;
	tok_t ret=0;

	for(i=num-1;i>=0;i--){
		add_hash_char(s[i],ret);
	}
	hash_finalize(ret);

	return ret;
}
