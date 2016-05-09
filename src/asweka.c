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

#define FREESTR() \
	for (i=0;i<strn;i++) \
		free(str[i]); \
	free(str);

SEXP ng_asweka(SEXP R_str, SEXP R_str_len, SEXP min_n_, SEXP max_n_, SEXP R_sep)
{
	int i, j;
	char **str, *sep;
	const char *tmp;
	const int min_n = INTEGER(min_n_)[0];
	const int max_n = INTEGER(max_n_)[0];
	const int strn = INTEGER(R_str_len)[0];
	int *str_lens;
	sentencelist_t *sl;
	ngramlist_t *ngl;
	wordlist_t *wptr;
	word_t **word_array;
	int numwords;
	int maxwordlen=0;
	int cur_n;
	char *buf;
	size_t len;

	SEXP RET, RET_NAMES, NGSIZE;
	SEXP str_ptr, sl_ptr, ngl_ptr;

	str = malloc((strn+1) * sizeof(*str));
	if (str == NULL)
		error("out of memory");
	str_lens = malloc(strn * sizeof(*str_lens));
	if (str_lens == NULL)
	{
		FREESTR();
		error("out of memory");
	}
	
	for(i=0;i<strn;i++){
		tmp = CHARPT(R_str, i);
		str_lens[i] = strlen(tmp);
		len = str_lens[i] + 1;
		str[i] = malloc((len+1) * sizeof(**str));
		strncpy(str[i], tmp, (len+1));
	}
	str[strn]=NULL;

	sep = CHARPT(R_sep, 0);
	if(*sep == '\0')
		sep=NULL;

	sl = lex_sentences((const char**)str, str_lens, strn, sep);
	free(str_lens);

	numwords = 0;
	for(i=0;i<sl->filled;i++)
		for(wptr=sl->words[i];wptr && wptr->word->s;wptr=wptr->next)
			numwords++;

	if (numwords == 0)
		error("no words");

	len = numwords;
	word_array = malloc(sizeof(*word_array)*numwords);
	if (word_array == NULL)
		error("out of memory");
	
	for(i=sl->filled-1;i>=0;i--){
		for(wptr=sl->words[i];wptr && wptr->word->s;wptr=wptr->next){
			word_array[--len]=wptr->word;

			if(wptr->word->len>maxwordlen)
				maxwordlen=wptr->word->len;
		}
	}

	buf = malloc(maxwordlen*max_n+max_n);
	if (buf == NULL)
	{
		free(word_array);
		error("out of memory");
	}

	i = numwords-(min_n-1);
	j = numwords-(max_n-1);
	len = i*(i+1)/2 - j*(j-1)/2;
	PROTECT(RET = allocVector(STRSXP, len));

	len = 0;
	for(cur_n=max_n;cur_n>=min_n;cur_n--){
		for(i=0;i<numwords-(cur_n-1);i++){
			memcpy(buf,word_array[i]->s,word_array[i]->len);
			buf[word_array[i]->len]=0;
			for(j=1;j<cur_n;j++){
				strcat(buf," ");
				strncat(buf,word_array[i+j]->s,word_array[i+j]->len);
			}
			SET_STRING_ELT(RET, len, mkChar(buf));
			len++;
		}
	}

	FREESTR();
	free(buf);
	free(word_array);
	free_sentencelist(sl,free_wordlist);

	UNPROTECT(1);
	return RET;
}
