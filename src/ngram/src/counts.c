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




