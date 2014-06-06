#include <stdbool.h>

#include "process.h"
#include "hash.h"
#include "print.h"
#include "wordcmp.h"
#include "hash.h"
#include "rand/rand.h"


#define OVERALLOC 20


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



int _ngram_cp_ng_to_char(ngram_t *ng, int *start, char *str)
{
  int i;
  int n = 0;
  int len;
  wordlist_t *wl = ng->words;
  word_t *word;
  
  while(wl)
  {
    word = wl->word;
    len = word->len;
    
    if (word == NULL)
      return n;
    
    for (i=0; i<len; i++)
      str[*start + i] = word->s[i];
    
    str[*start + len] = ' ';
    n += len + 1;
    
    *start += len+1;
    wl = wl->next;
  }
  
  return n;
}



int _ngram_cp_word_to_char(word_t *word, int start, char *str)
{
  int i;
  int n = 0;
  const int len = word->len;
  
  for (i=0; i<len; i++)
    str[start + i] = word->s[i];
    
  str[start + len] = ' ';
  n += len + 1;
  
  return n;
}



// Reverse-fill wordlist
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
  int i;
  int ret_ind = 0;
  int ng_ind = 0;
  int retlen = 0;
  bool init = true;
  const int maxlen = OVERALLOC * genlen;
  char *tmp;
  word_t *word;
  wordlist_t *wl;
  
  tmp = malloc(maxlen * sizeof(tmp));
  
  wl = NULL;
  for(i=0; i<n; i++)
    add_node(wl);
  
/*  printf("genlen = ");*/
  while (genlen > 0 && retlen < maxlen)
  {
    printf("%d ", genlen);
    // Initialize and/or restart after discovering NULL
    if (init)
    {
      while(init)
      {
        ng_ind = sample(rs, 0, ngsize-1);
        init = _ngram_check_ngram_for_null(&ng[ng_ind]);
      }
      
      genlen -= n-1;
      retlen += _ngram_cp_ng_to_char(&ng[ng_ind], &ret_ind, tmp);
    }
    
    // Get next word and put it into tmp
    word = _ngram_get_rand_nextword(rs, &ng[ng_ind]);
    if (word == NULL)
    {
      init = true;
      continue;
    }
    
    retlen += _ngram_cp_word_to_char(word, ret_ind, tmp);
    ret_ind += word->len + 1;
    ng_ind = _ngram_get_new_ng_index(n, wl, ng, ngsize, ng_ind, word);
    
    genlen--;
  }
  
  // Fix overallocation
  *ret = malloc(retlen * sizeof(**ret));
  for (i=0; i<retlen; i++)
    (*ret)[i] = tmp[i];
  
  printf("\n%d\n", retlen/2);
  
  free(tmp);
  
  return retlen;
}


