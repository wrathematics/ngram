#include "wordcmp.h"


char *word_to_string(word_t *word)
{
  int i;
  const int len = word->len;
  char *str;
  
  if(word != NULL)
  {
    str = malloc(len * sizeof(str));
    
    for(i=0; i<len; i++)
      str[i] = word->s[i];
    
    return str;
  }
  else
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


