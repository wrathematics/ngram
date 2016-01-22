/*  Copyright (c) 2014-2016, Schmidt, Heckendorf
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


#include "counts.h"
#include "common_defs.h"

/* Return the count for an ngram matching the given hash (tok) */
int find_ngram_count(ngramlist_t *ng, tok_t tok){
	int i;

	for(i=0;i<ng->ngsize;i++){
		if(ng->ng[i].tok==tok)
			return ng->ng[i].count;
	}

	return 0;
}


int ngram_counts_maxind(ngram_t *ng, int ngsize)
{
	int i;
	int ct, ct_best = 0;
	int ind = 0;
	nextwordlist_t *nwl;


	for (i=0; i<ngsize; i++)
	{
		nwl = ng[i].nextword;
		ct = 0;

		while (nwl)
		{
			ct += nwl->word.count;
			nwl = nwl->next;
		}

		if (ct > ct_best)
		{
			ct_best = ct;
			ind = i;
		}

	}

	return ind;
}



int ngram_counts_total(ngram_t *ng, int ngsize)
{
	int i;
	int ct = 0;
	nextwordlist_t *nwl;


	for (i=0; i<ngsize; i++)
	{
		nwl = ng[i].nextword;

		while (nwl)
		{
			ct += nwl->word.count;
			nwl = nwl->next;
		}
	}

	return ct;
}



int ngram_wordcount(const char *str, const char *sep)
{
	int i = 0;
	int ct = 0;

	if (str == NULL || str[0] == '\0')
		return 0;

	if(sep == NULL || *sep == '\0')
		return strlen(str);

	i+=strspn(str+i,sep); // skip initial
	while (str[i] != '\0')
	{
			i+=strcspn(str+i,sep); // find next sep
			ct++;
			i+=strspn(str+i,sep); // skip sep (find next word)
	}

	return ct;
}



int ngram_stringsummary(char *str, const int wordlen_max, ngram_summary_t *ngsum)
{
	ngsum->chars = 0, ngsum->letters = 0, ngsum->whitespace = 0, ngsum->punctuation = 0, ngsum->digits = 0;
	ngsum->words = 0, ngsum->sentences = 0, ngsum->lines = 1;
	char c;
	bool multispace_correction;
	int i = 0;
	int wordlen_current =  0;
	int *wordlens;

	ZEROINIT_MEM(wordlens,wordlen_max);

	while ((c=str[i]) != '\0')
	{
		ngsum->chars++;

		multispace_correction = false;
		if (isspace(c))
		{
			if (c != '\n')
				ngsum->whitespace++;
			else
				ngsum->lines++;

			ngsum->words++;
			wordlens[MIN(wordlen_current, wordlen_max)-1]++;
			wordlen_current =  0;
		}
		else
		{
			wordlen_current++;

			if (isalpha(c))
				ngsum->letters++;
			else if (isdigit(c))
				ngsum->digits++;
			else if (ispunct(c))
			{
				wordlen_current--;
				ngsum->punctuation++;

				if (i>0 && !ispunct(str[i-1]) && !isspace(str[i+1]))
				{
					ngsum->words++;
					wordlens[MIN(wordlen_current, wordlen_max)-1]++;
					wordlen_current =  0;
				}

				if (c=='.' || c==';' || c=='!' || c=='?')
					ngsum->sentences++;
			}
		}

		// skip multiple spaces
		do
		{
			if (isspace(c))
			{
				ngsum->chars++;
				if (c != '\n')
					ngsum->whitespace++;
				else
					ngsum->lines++;

				multispace_correction = true;
				i++;
			}
			else
				break;
		} while ((c=str[i]) != '\0');

		if (!multispace_correction)
			i++;
		else
		{
			ngsum->chars--;
			if (c!='\n' && str[i-1]!='\n')
				ngsum->whitespace--;
			else if (c=='\n' && str[i-1]=='\n')
				ngsum->lines--;
		}
	}

	c = str[i-1];
	if (!isspace(c))
	{
		ngsum->words++;
		wordlens[MIN(wordlen_current, wordlen_max)-1]++;
	}

	ngsum->wordlens = wordlens;

	return 0;
}


