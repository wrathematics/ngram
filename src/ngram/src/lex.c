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



static wordlist_t* split(const char *s, const int len){
	int i,j;
	wordlist_t *ret = NULL;

	for(i=0; i<len; i=j)
	{
		for(j=i; j<len && s[j] != ' '; j++)
			;
		add_node(ret);

		ret->word  =  malloc(sizeof(*ret->word));
		/*    if(() == NULL)*/
		/*      exit(1);*/

		ret->word->s = s+i;
		ret->word->len = j-i;
		while(j<len && s[j] == ' ')j++;
	}

	return ret;
}

wordlist_t* lex(const char *s, const int len){
	wordlist_t *words = split(s,len);
	wordlist_t *wp = words;

	while(wp){
		wp->word->tok = get_token(wp,1);
		wp = wp->next;
	}

	return words;
}
