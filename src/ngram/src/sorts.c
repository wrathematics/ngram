// Copyright 2014, Schmidt

#include <stdlib.h>
#include <string.h>


// this feels so leet ;-;
static inline void swap(void *a, void *b, size_t size)
{
  char *tmp = malloc(size);
  
  memcpy(tmp, b, size);
  memcpy(b, a, size);
  memcpy(a, tmp, size);
  
  free(tmp);
}

// sort y as a side effect (se) of sorting x
void ngram_sesort(int n, int *x, int *y)
{
  int i, j;
  
  for (i=1; i<n; i++)
  {
    j = i;
    
    while (j>0 && x[j-1] < x[j])
    {
      swap(x+j, x+j-1, sizeof(int));
      swap(y+j, y+j-1, sizeof(int));
      j--;
    }
  }
}

