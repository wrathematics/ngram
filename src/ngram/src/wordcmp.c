/*  Copyright (c) 2014, Schmidt
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


#include "wordcmp.h"
#include "common_defs.h"


char *word_to_string(word_t *word)
{
	int i;
	const int len = word->len;
	char *str;

	if(word != NULL)
	{
		INIT_MEM(str,len);

		for(i=0; i<len; i++)
			str[i] = word->s[i];

		return str;
	}

memerr:
	return NULL;
}



int wordcmp(word_t *word1, word_t *word2)
{
	int i;

	if (word1 == NULL)
	{
		if (word2 == NULL)
			return TRUE;
		else
			return FALSE;
	}
	else if (word1->len != word2->len)
		return FALSE;
	else
	{
		for(i=0; i<word1->len; i++)
		{
			if (word1->s[i] != word2->s[i])
				return FALSE;
		}

		return TRUE;
	}
}



int wordstrcmp(word_t *word, char *str, int strlen)
{
	int i;

	if (word == NULL)
	{
		if (strlen == 0)
			return TRUE;
		else
			return FALSE;
	}
	else if (word->len != strlen)
		return FALSE;
	else
	{
		for(i=0; i<word->len; i++)
		{
			if (word->s[i] != str[i])
				return FALSE;
		}

		return TRUE;
	}
}


