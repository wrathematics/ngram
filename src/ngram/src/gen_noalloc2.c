// Copyright 2014, Schmidt

#include <stdbool.h>

#include "process.h"
#include "hash.h"
#include "print.h"
#include "wordcmp.h"
#include "hash.h"
#include "rand/rand.h"


#define MIN(x,y) (x<y?x:y)


static void *vptr;

bool _ngram_check_ngram_for_null(ngram_t *ng)
{
  wordlist_t *wl = ng->words;
  
  while(wl)
  {
    if(wl->word == NULL)
      return true;
    
    wl = wl->next;
  }
  
  return false;
}



word_t* _ngram_get_rand_nextword(rng_state_t *rs, ngram_t *ng)
{
  int wordtot = 0;
  int ind;
  int tmp = 0;
  word_t *word;
  
  nextwordlist_t *nwl = ng->nextword;
  
  
  // Get "index" of next word
  while(nwl)
  {
    wordtot += nwl->word.count;
    nwl = nwl->next;
  }
  
  ind = sample(rs, 0, wordtot-1) + 1;
  nwl = ng->nextword;
  
  // Get the word
  while(1)
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



int _ngram_cp_ng_to_char(int num, ngram_t *ng, int *ind, char **str, int *len)
{
  int n = 0;
  wordlist_t *wl = ng->words;
  word_t *word;
  
  while(wl && num > 0)
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



static inline int _ngram_cp_word_to_char(word_t *word, int *ind, char **str, int *len)
{
  len[*ind] = word->len;
  
  str[*ind] = (char *) word->s;
  
  return len[*ind] + 1;
}



wordlist_t* _ngram_reverse_fill_wordlist(wordlist_t *dst, wordlist_t *src)
{
  if(src->next!=NULL)
    dst = _ngram_reverse_fill_wordlist(dst,src->next);
  
  dst->word = src->word;
  
  return dst->next;
}


int _ngram_get_new_ng_index(const int n, wordlist_t *wl, ngram_t *ng, const int ngsize, const int ng_ind, word_t *word)
{
  int i;
  tok_t hash;
  wordlist_t *wl_old = ng[ng_ind].words->next;
  
  _ngram_reverse_fill_wordlist(wl->next,wl_old); 
  wl->word=word;
  
  hash = get_token(wl, n);
  
  for (i=0; i<ngsize; i++)
  {
    if (ng[i].tok == hash)
      return i;
  }
  
  // Something went wrong
  return -1;
}



// genlen = #words
int ngram_gen(const int n, rng_state_t *rs, ngram_t *ng, int ngsize, int genlen, char **ret)
{
  int i, j, pos;
  int ng_ind = 0;
  int retlen = 0;
  bool init = true;
  char **tmp;
  int *itmp;
  const int genlencp = genlen; // this is the kind of shit you get when you plan ahead poorly
  word_t *word;
  wordlist_t *wl;
  
  if (genlen < 1)
    return -1;
  else if (n > genlen)
    genlen = n;
  
  tmp = malloc(genlen * sizeof(tmp));
  itmp = malloc(genlen * sizeof(itmp));
  
  wl = NULL;
  for(i=0; i<n; i++)
    add_node(wl);
  
  i = 0;
  
  while (genlen > 0)
  {
    if (init)
    {
      while (init)
      {
        ng_ind = sample(rs, 0, ngsize-1);
        init = _ngram_check_ngram_for_null(&ng[ng_ind]);
      }
      
      retlen += _ngram_cp_ng_to_char(MIN(n, genlen), &ng[ng_ind], &i, tmp, itmp);
      genlen -= n;
    }
    else
    {
      // Get next word and put it into tmp
      word = _ngram_get_rand_nextword(rs, &ng[ng_ind]);
      if (word == NULL)
      {
        init = true;
        continue;
      }
      
      retlen += _ngram_cp_word_to_char(word, &i, tmp, itmp);
      ng_ind = _ngram_get_new_ng_index(n, wl, ng, ngsize, ng_ind, word);
      i++;
      genlen--;
    }
  }
  
  
  // Wrangle return string
  pos = 0;
  *ret = malloc(retlen * sizeof(**ret));
  for (i=0; i<genlencp; i++)
  {
    for (j=0; j<itmp[i]; j++)
    {
      (*ret)[pos] = tmp[i][j];
      pos++;
    }
    (*ret)[pos++] = ' ';
  }
  
  
  free(wl);
  free(tmp);
  free(itmp);
  
  return retlen;
}

