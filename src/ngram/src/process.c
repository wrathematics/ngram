/*  Copyright (c) 2014-2019, Heckendorf and Schmidt
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


#include <string.h>

#include "process.h"
#include "common_defs.h"

static void *vptr;


void free_ngl(ngramlist_t *ngl)
{
	int i;

	for (i=0; i<ngl->ngsize; i++)
	{
		free_list(ngl->ng[i].words);
		free_list(ngl->ng[i].nextword);
	}

	free(ngl->ng);
	free(ngl->order);
	free(ngl);
}


static int cmp_ngram(const void *a, const void *b){
	ngram_t **na = (ngram_t**)a;
	ngram_t **nb = (ngram_t**)b;

	if((*na)->tok<(*nb)->tok)
		return -1;
	else if((*na)->tok>(*nb)->tok)
		return 1;
#ifdef NEXTWORDS
	else{
		if((*na)->nextword->word.word == NULL)
			return -1;
		else if((*nb)->nextword->word.word == NULL)
			return 1;
		else if((*na)->nextword->word.word->tok<(*nb)->nextword->word.word->tok)
			return -1;
		else if((*na)->nextword->word.word->tok>(*nb)->nextword->word.word->tok)
			return -1;
	}
#endif
	return 0;
}



ngramlist_t* process(sentencelist_t *wordtok, int n)
{
	int i, j, k, js, len, ngsize, endi;
	int *sen_len = NULL;
	wordlist_t *p, *q, *nw;
	ngram_t *ng = NULL, *tmp = NULL, **sorted = NULL;
	ngramlist_t *ngl = NULL;

	if (n<1)
		return NULL;

	INIT_MEM(sen_len,wordtok->filled);

	INIT_MEM(ngl,1);
	ngl->ngsize = 0;

	len = 0;
	for(i=0;i<wordtok->filled;i++){
		sen_len[i] = 0;
		p = wordtok->words[i];
		while (p){
			sen_len[i]++;
			p = p->next;
		}
		sen_len[i] -= n-1;
		if(sen_len[i]<0)
			sen_len[i]=0;

		len += sen_len[i];
	}

	if (len<1)
		goto memerr;

	INIT_MEM(ng,len);
	INIT_MEM(ngl->order,len);
	ng->count = 0;

	ZEROINIT_MEM(tmp,len);
	INIT_MEM(sorted,len);

	endi=0;
	i=0;
	for(j=0;j<wordtok->filled;j++){
		if(sen_len[j]<1)
			continue;

		/* Add the final ngram to the start of tmp, no nextwords, words stored end:start */
		nw = q = p = wordtok->words[j];
		tmp[i].tok = get_token(p,n);
		tmp[i].words = NULL;
		for (k = 0;q && k<n;k++){
			add_node(tmp[i].words);
			tmp[i].words->word = q->word;
			q = q->next;
		}
		tmp[i].nextword = NULL;
#ifdef NEXTWORDS
		add_node(tmp[i].nextword);
		tmp[i].nextword->word.word = NULL;
		tmp[i].nextword->word.count = 1;
#endif
		sorted[endi] = tmp+i;

		/* Add the remaining ngrams iteratively */
		i = endi+1;
		endi += sen_len[j];
		for (;nw && i<endi;i++){
			q = p = nw->next;
			tmp[i].tok = get_token(p,n);
			tmp[i].words = NULL;
			for (k = 0;q && k<n;k++){
				add_node(tmp[i].words);
				tmp[i].words->word = q->word;
				q = q->next;
			}
			tmp[i].nextword = NULL;
#ifdef NEXTWORDS
			add_node(tmp[i].nextword);
			tmp[i].nextword->word.word = nw->word;
			tmp[i].nextword->word.count = 1;
#endif

			sorted[i] = tmp+i;

			nw = nw->next;
		}
	}

	qsort(sorted,len,sizeof(*sorted),cmp_ngram);

	ngsize = 0;
	for (i = 0;i<len;i = j) {
		js = i;
		for (j = i+1;j<len && sorted[j]->tok == sorted[i]->tok;j++){
#ifdef NEXTWORDS
			if ((sorted[js]->nextword->word.word != NULL &&
				  sorted[j]->nextword->word.word != NULL &&
				  sorted[j]->nextword->word.word->tok == sorted[js]->nextword->word.word->tok) || /* same string, or... */
				  sorted[j]->nextword->word.word == sorted[js]->nextword->word.word) /* both NULLs (sentence ends) */
				sorted[js]->nextword->word.count++;
			else {
				add_node(sorted[js]->nextword);
				sorted[js]->nextword->word.count = 1;
				sorted[js]->nextword->word.word = sorted[j]->nextword->word.word;
			}
			free_list(sorted[j]->nextword);
#endif
			free_list(sorted[j]->words);
		}
#ifdef NEXTWORDS
		//if (j == i+1)
			//sorted[i]->nextword->word.count = 1;
#endif

		ng[ngsize].count = j-i;
		ng[ngsize].words = sorted[i]->words;
		ng[ngsize].nextword = sorted[i]->nextword;
		ng[ngsize].tok = sorted[i]->tok;
		ngl->order[ngsize] = sorted[j-1]-tmp;
		ngsize++;
	}

	free(sen_len);
	free(sorted);
	free(tmp);

	ngl->ng = ng;
	ngl->ngsize = ngsize;
	ngl->n = n;

	return ngl;

memerr:
	freeif(sen_len);
	freeif(ngl);
	freeif(ng);
	if(tmp){
		for(i=0;i<len;i++){
			free_list(tmp[i].words);
#ifdef NEXTWORDS
			free_list(tmp[i].nextword);
#endif
		}
		free(tmp);
	}
	freeif(sorted);
	return NULL;
}
