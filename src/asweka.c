/*  Copyright (c) 2016, Heckendorf
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


#include "ngram.h"

SEXP R_ng_asweka(SEXP R_str, SEXP min_n_, SEXP max_n_, SEXP R_sep)
{
	int i, j;
	char *str = CHARPT(R_str, 0); 
	char *sep = CHARPT(R_sep, 0); 
	const int min_n = INTEGER(min_n_)[0];
	const int max_n = INTEGER(max_n_)[0];
	int str_len;
	sentencelist_t *sl;
	wordlist_t *wptr;
	int numwords;
	int cur_n;
	size_t len;
	const char **starts = NULL;
	int *lens = NULL;
	int word_i;
	char *errstr;

	SEXP RET;

	str_len = strlen(str);

	if(*sep == '\0')
		sep=NULL;

	sl = lex_simple(str, str_len, sep);

	if (sl == NULL)
		error("out of memory");

	numwords = 0;
	for(i=0;i<sl->filled;i++)
		for(wptr=sl->words[i];wptr && wptr->word->s;wptr=wptr->next)
			numwords++;

	if (numwords == 0){
		errstr="no words";
		goto memerr;
	}

	len = numwords;
	starts = malloc(sizeof(*starts)*numwords);
	if (starts == NULL){
		errstr="out of memory";
		goto memerr;
	}

	lens = malloc(sizeof(*lens)*numwords);
	if (lens == NULL){
		errstr="out of memory";
		goto memerr;
	}
	
	for(i=sl->filled-1;i>=0;i--){
		for(wptr=sl->words[i];wptr && wptr->word->s;wptr=wptr->next){
			--len;
			starts[len]=wptr->word->s;
			lens[len]=wptr->word->len;
		}
	}

	i = numwords-(min_n-1);
	j = numwords-(max_n-1);
	len = i*(i+1)/2 - j*(j-1)/2;
	PROTECT(RET = allocVector(STRSXP, len));

	word_i = 0;
	for(cur_n=max_n;cur_n>=min_n;cur_n--){
		for(i=0;i<numwords-(cur_n-1);i++){
			len = starts[i+cur_n-1] - starts[i] + lens[i+cur_n-1]; 
			SET_STRING_ELT(RET, word_i, mkCharLen(starts[i], len));
			
			word_i++;
		}
	}

	free(starts);
	free(lens);
	free_sentencelist(sl,free_wordlist);

	UNPROTECT(1);
	return RET;

memerr:
	freeif(starts);
	freeif(lens);
	free_sentencelist(sl,free_wordlist);
	Rf_error("%s", errstr);
}
