// I apologize to the world for the abomination that is this file

#include <stdbool.h>

#include "process.h"
#include "hash.h"
#include "print.h"
#include "wordcmp.h"
#include "hash.h"
#include "rand/rand.h"


#define OVERALLOC 20


static void *vptr;

bool check_ngram_for_null(ngram_t *ng)
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



word_t *get_rand_nextword(rng_state_t *rs, ngram_t *ng)
{
  int wordtot = 0;
  int ind;
  int tmp = 0;
  word_t *word;
  
  nextwordlist_t *nwl = ng->nextword;
  
  
  while(nwl)
  {
/*    if(wl->word == NULL)*/
/*      return wordtot;*/
    
    wordtot += nwl->word.count;
    nwl = nwl->next;
  }
  
  ind = sample(rs, 0, wordtot-1) + 1;
  printf("%d\n", ind);
  nwl = ng->nextword;
  
  while(1)
  {
    // FIXME
/*    if(word == NULL)*/
/*      return wordtot;*/
    
    tmp += nwl->word.count;
    
    printf("%d %d %d\n", tmp, nwl->word.count, ind);
    if (tmp >= ind)
    {
      word = nwl->word.word;
      break;
    }
    
    nwl = nwl->next;
  }
  
  print_word(word);
  
  return word;
}



int cp_ng_to_char(ngram_t *ng, int *start, char *str)
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



int cp_word_to_char(word_t *word, int start, char *str)
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



int get_new_ng_index(ngram_t *ng, const int ngsize, const int ng_ind, word_t *word)
{
  const int n = 3; //FIXME
  int i;
  tok_t hash;
  wordlist_t *wl;
  wordlist_t *wl_old = ng[ng_ind].words->next;
  
  
  wl = NULL;
  
  for(i=0; i<n-1; i++)
  {
    add_node(wl);
    wl->word = wl_old->word;
    
    wl_old = wl_old->next;
  }
  
  add_node(wl);
  wl->word = word;
  
  hash = get_token(wl, n);
  
  free(wl);
  
  for (i=0; i<ngsize; i++)
  {
    if (ng[i].tok == hash)
      return i;
  }
  
  // Something went wrong
  return -1;
}



// genlen = #words
int gen(rng_state_t *rs, ngram_t *ng, int ngsize, int genlen, char **ret)
{
  int i;
  int ret_ind = 0;
  int ng_ind = 0;
  int n = 0;
  bool init = true;
  char *tmp;
  word_t *word;
  
  tmp = malloc(OVERALLOC * genlen * sizeof(tmp));
  
  while (genlen)
  {
    // Initialize and/or restart after discovering NULL
    while (init)
    {
      ng_ind = sample(rs, 0, ngsize-1);
      printf("------------%d------------\n", ng_ind);
      //ng_ind = 29718; //FIXME DELETEME
      //ng_ind = 102277;
      init = check_ngram_for_null(&ng[ng_ind]); //TODO do something with this
      init = false; //FIXME
      
      print_ngram(&ng[ng_ind]);
      
      n += cp_ng_to_char(&ng[ng_ind], &ret_ind, tmp);
    }
    
    // Get next word and put it into tmp
    
    word = get_rand_nextword(rs, &ng[ng_ind]);
    n += cp_word_to_char(word, ret_ind, tmp);
    ret_ind += word->len + 1;
    
    // Reset ng and cycle
/*    n += cp_ng_to_char(&ng[ng_ind], &ret_ind, tmp);*/
    
    ng_ind = get_new_ng_index(ng, ngsize, ng_ind, word);
    
    printf("%d\n", ng_ind);
    if (ng_ind != -1)
      print_ngram(&ng[ng_ind]);
    
    genlen--;
  }
  
  // Fix overallocation
  *ret = malloc(n * sizeof(**ret));
  for (i=0; i<n; i++)
    (*ret)[i] = tmp[i];
  
  free(tmp);
  
  return n;
}


