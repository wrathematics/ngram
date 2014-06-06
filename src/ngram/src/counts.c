#include "print.h"



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
  
  if (str[0] == '\0')
    return 0;
  
  if (str[0] != sep)
    ct++;
  
  while(1)
  {
    if (str[i] == '\0')
      break;
    else if (str[i] == sep && str[i-1] != sep && str[i+1] != sep && str[i+1] != '\0')
      ct++;
    
    i++;
  }
  
  return ct;
}



