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


#include <stdbool.h>

#include "lex.h"
#include "hash.h"
#include "wordcmp.h"
#include "process.h"
#include "rand/rand.h"
#include "common_defs.h"


#define MIN(x,y) (x<y?x:y)


static void *vptr;

static bool ngram_check_ngram_for_null(ngram_t *ng)
{
  wordlist_t *wl = ng->words;
  
  while (wl)
  {
    if (wl->word == NULL)
      return true;
    
    wl = wl->next;
  }
  
  return false;
}



static word_t* ngram_get_rand_nextword(rng_state_t *rs, ngram_t *ng)
{
  int wordtot = 0;
  int ind;
  int tmp = 0;
  word_t *word = NULL;
  
  nextwordlist_t *nwl = ng->nextword;
  
  
  // Get "index" of next word
  while (nwl)
  {
    wordtot += nwl->word.count;
    nwl = nwl->next;
  }
  
  ind = sample(rs, 0, wordtot-1) + 1;
  nwl = ng->nextword;
  
  // Get the word
  while (nwl)
  {
    tmp += nwl->word.count;
    
    if (tmp >= ind)
    {
      word = nwl->word.word;
      break;
    }
    
    nwl = nwl->next;
  }
  
  return word;
}



static int ngram_cp_ng_to_char(int num, ngram_t *ng, int *ind, char **str, int *len)
{
  int n = 0;
  wordlist_t *wl = ng->words;
  word_t *word;
  
  while (wl && num > 0)
  {
    word = wl->word;
    len[*ind] = word->len;
    
    if (word == NULL)
      return n;
    
    str[*ind] = (char *) word->s;
    
    n += len[*ind] + 1;
    
    wl = wl->next;
    num--;
    (*ind)++;
  }
  
  return n;
}



static inline int ngram_cp_word_to_char(word_t *word, int *ind, char **str, int *len)
{
  len[*ind] = word->len;
  
  str[*ind] = (char *) word->s;
  
  return len[*ind] + 1;
}



static wordlist_t* ngram_reverse_fill_wordlist(wordlist_t *dst, wordlist_t *src)
{
  if (src == NULL) return dst;
  
  if (src->next != NULL)
    dst = ngram_reverse_fill_wordlist(dst, src->next);
  
  dst->word = src->word;
  
  
  return dst->next;
}



static ngram_t* ngram_get_new_ng(const int n, wordlist_t **wl_end, ngram_t *ng, word_t *word, struct hashtable *htab)
{
  wordlist_t *wl = *wl_end;
  ngram_t tmp_ng;
  int i;

  /* circularize, put word in the first slot, shift pointers to next (old first becomes end), break circle */
  ng->words->word = word;
  (*wl_end)->next = ng->words;
  *wl_end = ng->words;
  ng->words = ng->words->next;
  (*wl_end)->next = NULL;

  ng->tok = get_token(ng->words, n);

  return get_hashtable_value_ngram(ng, htab);
}

static wordlist_t* ngram_copy_wordlist(wordlist_t *dst, wordlist_t *src){
  wordlist_t *p = dst;

  while(src != NULL){
    dst->word = src->word;
    dst = dst->next;
    src = src->next;
  }

  return p;
}


// genlen = #words
int ngram_gen(rng_state_t *rs, ngramlist_t *ngl, int genlen, char **ret)
{
  int i, j, pos;
  const int n = ngl->n;
  const int ngsize = ngl->ngsize;
  ngram_t *ng = ngl->ng, *t_ng, tmp_ng;
  int ng_ind = 0;
  int retlen = 0;
  bool init = true;
  char **tmp = NULL;
  int *itmp = NULL;
  const int genlencp = genlen; // this is the kind of shit you get when you plan ahead poorly
  word_t *word;
  wordlist_t *wl = NULL;
  wordlist_t *wl_end = NULL;
  wordlist_t *wl_start = NULL;
  
  *ret = NULL;
  
  if (genlen < 1)
    return -1;
  else if (genlen < n)
    genlen = n;
  
  if (n < 1)
    return -1;
  
  INIT_MEM(tmp,genlen);
  ZEROINIT_MEM(itmp,genlen);
  
  wl = NULL;
  for (i=0; i<n; i++)
    add_node(wl);
  
  i = 0;
  
  wl_start = wl_end = wl;
  while(wl_end->next)
    wl_end=wl_end->next;

  while (genlen > 0)
  {
    if (init)
    {
      while (init)
      {
        ng_ind = sample(rs, 0, ngsize-1);
        t_ng = ng + ng_ind;
        init = ngram_check_ngram_for_null(t_ng);
      }

      tmp_ng.words = ngram_copy_wordlist(wl, t_ng->words);
      tmp_ng.nextword = t_ng->nextword;

      retlen += ngram_cp_ng_to_char(MIN(n, genlen), t_ng, &i, tmp, itmp);
      genlen -= n;
    }
    else
    {
      // Get next word and put it into tmp
      word = ngram_get_rand_nextword(rs, &tmp_ng);
      if (word == NULL)
      {
        init = true;
        continue;
      }
      
      retlen += ngram_cp_word_to_char(word, &i, tmp, itmp);
      t_ng = ngram_get_new_ng(n, &wl_end, &tmp_ng, word, ngl->htab);
      if(t_ng)
        tmp_ng.nextword = t_ng->nextword;
      i++;
      genlen--;
    }
  }
  
  
  // Wrangle return string
  retlen = retlen==0 ? genlencp : retlen; // quiet the static analyzer
  
  pos = 0;
  INIT_MEM(*ret,retlen);
  for (i=0; i<genlencp; i++)
  {
    for (j=0; j<itmp[i]; j++)
    {
      (*ret)[pos] = tmp[i][j];
      pos++;
    }
    (*ret)[pos++] = ' ';
  }
  
  
  free_wordlist_keepwords(wl_start);
  free(tmp);
  free(itmp);
  
  return retlen;

memerr:
  freeif(tmp);
  freeif(itmp);
  free_wordlist_keepwords(wl_start);
  freeif(*ret);

  return -1;
}
