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


#include "lex.h"
#include "hash.h"
#include "common_defs.h"

static void *vptr;

void free_wordlist(wordlist_t *wl)
{
	while(wl)
	{
		vptr = wl->next;
		if(wl->word)
			free(wl->word);

		free(wl);
		wl = vptr;
	}
}


void free_wordlist_keepwords(wordlist_t *wl)
{
	while(wl)
	{
		vptr = wl->next;
		free(wl);
		wl = vptr;
	}
}

void free_sentencelist(sentencelist_t *sl, void(*wlcb)(wordlist_t*))
{
	int i;

	for(i=0;i<sl->filled;i++)
		wlcb(sl->words[i]);

	free(sl->words);
	free(sl);
}


/*
static int strchrs(const char c, const char *sep){
	if(sep==NULL || *sep == 0)
		return 1;

	while(*sep){
		if(c==*sep)
			return 1;
		sep++;
	}
	return 0;
}
*/

static wordlist_t* split(const char *s, const int len, const char *sep){
	int i,j;
	wordlist_t *ret = NULL;

	for(j=i=0; i<len; i=j)
	{
		//for(j=i; j<len && !strchrs(s[j],sep); j++)
			//;
		if(sep)
			j=i+strcspn(s+i,sep);
		else
			j++;

		add_node(ret);

		INIT_MEM(ret->word,1);

#ifndef SINGLES
		ret->word->s = s+i;
		ret->word->len = j-i;
#else
		ret->word->c = s[i];
		ret->word->s = &ret->word->c;
		ret->word->len = 1;
#endif

		//while(j<len && strchrs(s[j],sep))j++;
		if(sep)
			j+=strspn(s+j,sep);
	}

	return ret;

memerr:
	free_wordlist(ret);
	return NULL;
}

static wordlist_t* lex(const char *s, const int len, const char *sep){
	wordlist_t *words = split(s,len,sep);
	wordlist_t *wp = words;

	while(wp){
		wp->word->tok = get_token(wp,1);
		wp = wp->next;
	}

	return words;
}

sentencelist_t* lex_init(const int num){
	sentencelist_t *ret;
	int i;

	INIT_MEM(ret,1);
	INIT_MEM(ret->words,num);

	for(i=0;i<num;i++)
		ret->words[i]=NULL;

	ret->len=num;
	ret->filled=0;

	return ret;

memerr:
	freeif(ret);
	return NULL;
}

int lex_add(sentencelist_t *wordtok, const int index, const char *s, const int len, const char *sep){
	if(index >= wordtok->len)
		return -1; // silent fail :(

	wordtok->words[index] = lex(s,len,sep);
	if(wordtok->words[index] == NULL)
		return -1;

	wordtok->filled++;

	return 0;
}

sentencelist_t* lex_sentences(const char **s, const int *lengths, const int num, const char *sep){
	sentencelist_t *ret;
	int i;

	ret = lex_init(num);
	if(ret == NULL)
		return NULL;

	for(i=0;i<num;i++)
		if(lex_add(ret,i,s[i],lengths[i],sep))
			goto memerr;

	return ret;

memerr:
	free_sentencelist(ret,free_wordlist);
	return NULL;
}

sentencelist_t* lex_simple(const char *s, const int len, const char *sep){
	return lex_sentences(&s,&len,1,sep);
}
