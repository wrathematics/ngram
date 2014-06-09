#include "print.h"


#define NOTNUL(x) (x[i] != '\0')


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


int ngram_wordcount(const char *str, const char sep)
{
  int i = 0;
  int ct = 0;
  
  if (str == NULL || str[0] == '\0')
    return 0;
  
  while (str[i] == sep)
    i++;
  
  while (str[i] != '\0')
  {
    while (str[i] == sep)
      i++;
    
    if (str[i] != sep && str[i] != '\0')
      ct++;
    
    while (str[i] != sep && str[i] != '\0')
      i++;
  }
  
  return ct;
}

#if 0 // fuck this, I'll do it later
void ngram_wordcount_checksep(int *i, const char *str, const char *sep, const int seplen)
{
  int j;
  
  while(1)
  {
    for (j=0; j<seplen && str[*i+j] == sep[j]; j++){}
    
    if (j == seplen)
      *i += j;
    else
      break;
  }
}

int ngram_wordcount(const char *str, const char *sep, const int seplen)
{
  int i, j, tmp;
  int ct = 0;
  
  if (str == NULL || str[0] == '\0')
    return 0;
  
  i = 0;
  
  ngram_wordcount_checksep(&i, str, sep, seplen);
  
  for (i=0; i<4; i++)
/*  while (str[i] != '\0')*/
  {
    printf("%d", i);
    ngram_wordcount_checksep(&i, str, sep, seplen);
    printf("%d\n", i);
    
    if (str[i] != '\0')
      ct++;
    
    while (str[i] != sep[0] && str[i] != '\0')
      i++;
  }
  
  return ct;
}
#endif




