// Copyright 2014, Heckendorf

#include "lex.h"
#include "hash.h"

static void *vptr;

void free_wordlist(wordlist_t *wl){
  while(wl){
    vptr = wl->next;
    if(wl->word)
      free(wl->word);
    free(wl);
    wl = vptr;
  }
}

static wordlist_t* split(const char *s, const int len){
  int i,j;
  wordlist_t *ret = NULL;

  for(i = 0;i<len;i = j){
    for(j = i;j<len && s[j] != ' ';j++)
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
